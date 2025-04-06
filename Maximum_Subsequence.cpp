#include<iostream>
#include<algorithm>
using namespace std;
const int MN=40;
int n,m,mid,cnt1,cnt2;
int a[MN],fr[MN],bk[MN];
void dfs1(int x,int v){
    if(x==mid){
        fr[++cnt1]=v;
        fr[++cnt1]=(v+a[x])%m;
        return;
    }
    dfs1(x+1,v);
    dfs1(x+1,(v+a[x])%m);
}
void dfs2(int x,int v){
    if(x==n){
        bk[++cnt2]=v;
        bk[++cnt2]=(v+a[x])%m;
        return;
    }
    dfs2(x+1,v);
    dfs2(x+1,(v+a[x])%m);
}
int main(){
    cin>>n>>m;
    mid=n>>1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    dfs1(1,0);
    dfs2(mid+1,0);
    sort(fr+1,fr+1+cnt1);
    sort(bk+1,bk+cnt2+1);
    int ans=-1;
    int i=0,j=cnt2;
    
    for(;i<=cnt1;i++){
        while (fr[i]+bk[j]>=m)
        {
            j--;
        }
        ans=max(ans,fr[i]+bk[j]);
    }
    ans=max(ans,fr[i]+bk[j]-m);
    cout<<ans;
    return 0;
}