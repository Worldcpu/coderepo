#include<bits/stdc++.h>
using namespace std;
constexpr int MN=66;
int n,cnt,len,maxx,sum,a[MN];
bool vis[MN];

bool cmp(int x,int y){
    return x>y;
}

bool dfs(int p,int nlen,int lst){
    if(p>cnt) return 1;
    if(nlen==len) return dfs(p+1,0,1);
    int fail=0;
    for(int i=lst;i<=n;i++){
        if(!vis[i]&&nlen+a[i]<=len&&fail!=a[i]){
            vis[i]=1;
            if(dfs(p,nlen+a[i],i+1)) return 1;
            fail=a[i];
            vis[i]=0;
            if(!nlen||nlen+a[i]==len) return 0;
        }
    }
    return 0;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
        maxx=max(maxx,a[i]);
    }
    sort(a+1,a+1+n,cmp);
    for(len=maxx;len<=sum;len++){
        if(sum%len) continue;
        cnt=sum/len;
        memset(vis,0,sizeof(vis));
        if(dfs(1,0,1)) break;
    }
    cout<<len;
    return 0;
}
