#include<bits/stdc++.h>
using namespace std;
const int MN=520;
int n,m,nxt[MN],a[MN],sum,mxlen;
bool vis[MN];
bool cmp(int x,int y){
    return x>y;
}
bool dfs(int len,int pre,int now){
    if(pre%len==0){
        if(sum-pre==len) return 1;
        int i;
        for(i=2;i<=m&&vis[i];i++);
        vis[i]=1;
        if(dfs(len,pre+a[i],2))return 1;
        vis[i]=0;
    }else{
        for(int i=now;i<=m;i++){
            if(!vis[i]){
                if(pre%len+a[i]<=len){
                    vis[i]=1;
                    if(dfs(len,pre+a[i],i))return 1;
                }
                vis[i]=0;
                if(pre%len+a[i]==len) return 0;
            }
            i=nxt[a[i]];
        }
    }
    return 0;
}
int main(){
    int pre=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        int tmp;
        cin>>tmp;
        if(tmp<=50){
            a[++m]=tmp;
            mxlen=max(mxlen,tmp);
            sum+=tmp;
        }
    }
    sort(a+1,a+1+m,cmp);
    for(int i=1;i<=m;i++){
        if(a[i]!=pre){
            nxt[pre]=i-1;
            pre=a[i];
        }
    }
    nxt[pre]=m+1;
    vis[1]=1;
    int i;
    for(i=mxlen;i<=sum/2;i++){
        if(sum%i!=0) continue;
        if(dfs(i,a[1],2))break;
    }
    if(i>sum/2)cout<<sum;
    else cout<<i;
    return 0;
}