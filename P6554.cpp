#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN];
double f[MN],g[MN],ans=-1e18;
vector<int> adj[MN];

namespace Tree{
    int lf1[MN],lf2[MN],dg[MN];

    void dfs1(int u,int pre){
        if(dg[u]==1&&u!=1){
            f[u]=a[u];
            lf1[u]=1;
            return;
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            lf1[u]+=lf1[v];
            f[u]+=lf1[v]*f[v];
        }
        f[u]/=lf1[u];
        f[u]+=a[u];
    }

    void dfs2(int u,int pre){
        if(dg[pre]==1){
            g[u]=a[pre]+a[u];
            lf2[u]=1;
        }else{
            lf2[u]=lf2[pre]+lf1[pre]-lf1[u];
            g[u]=(g[pre]*lf2[pre]+f[pre]*lf1[pre]-(f[u]+a[pre])*lf1[u])/lf2[u]+a[u];
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs2(v,u);
        }
    }

}using namespace Tree;

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        dg[u]++,dg[v]++;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    dfs1(1,0);
    for(auto v:adj[1]) dfs2(v,1);
    for(int i=1;i<=n;i++){
        if(dg[i]==1&&i!=1){
            ans=max(ans,g[i]);
        }else{
            ans=max(ans,(f[i]*lf1[i]+g[i]*lf2[i])/(lf1[i]+lf2[i]));
        }
    }
    cout<<fixed<<setprecision(6)<<ans<<'\n';
    return 0;
}