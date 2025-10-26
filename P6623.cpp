#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MV=21,MN=1<<21;
int n,f[MV][MN],v[MN],ans;
vector<int> adj[MN];

namespace Tree{
    int dep[MN];

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
        }
    }

    int dfs2(int u,int pre){
        int ret=v[u];
        for(int i=0;i<MV;i++){
            f[i][(dep[u]+v[u])&((1<<i)-1)]^=1<<i;
        }
        for(int i=0;i<MV;i++){
            ret^=f[i][(dep[u])&((1<<i)-1)];
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            ret^=dfs2(v,u);
        }
        for(int i=0;i<MV;i++){
            ret^=f[i][(dep[u])&((1<<i)-1)];
        }
        ans+=ret;
        return ret;
    }

}using namespace Tree;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        adj[x].push_back(i);
    }
    dfs1(1,0);
    dfs2(1,0);
    cout<<ans;
    return 0;
}