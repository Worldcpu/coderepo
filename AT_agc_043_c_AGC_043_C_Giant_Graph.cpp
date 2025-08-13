#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4e5+15,MOD=998244353;
const int base=1000000000000000000ll %MOD;
int n,ans;

struct Graph{
    int sg[MN],f[MN],mxsg;
    bool vis[MN];
    vector<int> adj[MN];

    void dfs(int u){
        if(vis[u]) return;
        vis[u]=1;
        set<int> st;
        for(auto v:adj[u]){
            dfs(v);
            st.insert(sg[v]);
        }
        sg[u]=0;
        while(st.find(sg[u])!=st.end()) sg[u]++;
    }
    
    void init(){
        int m;
        cin>>m;
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            if(u>v) swap(u,v);
            adj[u].push_back(v);
        }
        for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
        int x=1;
        for(int i=1;i<=n;i++){
            mxsg=max(mxsg,sg[i]);
            x=x*base%MOD;
            f[sg[i]]=(f[sg[i]]+x)%MOD;
        }
    }

}g[3];

signed main(){
    cin>>n;
    for(int i=0;i<3;i++) g[i].init();
    for(int i=0;i<=g[0].mxsg;i++){
        for(int j=0;j<=g[1].mxsg;j++){
            ans=(ans+g[0].f[i]*g[1].f[j]%MOD*g[2].f[i^j]%MOD)%MOD;
        }
    }
    cout<<ans;
    

    return 0;
}