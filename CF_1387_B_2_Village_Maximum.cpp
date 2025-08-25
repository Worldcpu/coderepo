#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,rt,ttot,sum,tmp[MN],ans[MN];
vector<int> adj[MN];

namespace Tree{
    int siz[MN],maxp[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        maxp[u]=0;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            maxp[u]=max(maxp[u],siz[v]);
            sum+=2*min(siz[v],n-siz[v]);
        }
        maxp[u]=max(maxp[u],n-siz[u]);
        if(maxp[u]<maxp[rt]) rt=u;
    }

    void dfs2(int u,int pre){
        tmp[++ttot]=u;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs2(v,u);
        }
    }

}using namespace Tree;


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    maxp[rt]=n;
    dfs1(1,0);
    dfs2(rt,0);
    cout<<sum<<'\n';
    for(int i=1;i<=n;i++){
        ans[tmp[i]]=tmp[(i+n/2-1)%n+1];
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';

    return 0;
}