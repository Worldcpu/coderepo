#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=3e6+15;
int n;
ll buf[MN],ans,*f[MN],*g[MN],*now;
vector<int> adj[MN];

namespace Tree{
    int dep[MN],mxdep[MN],len[MN],fa[MN],hson[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=mxdep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            if(mxdep[u]<mxdep[v]){
                mxdep[u]=mxdep[v];
                hson[u]=v;
            }
        }
        len[u]=mxdep[u]-dep[u]+1;
    }

    void dfs3(int u,int pre){
        if(hson[u]){
            f[hson[u]]=f[u]+1;
            g[hson[u]]=g[u]-1;
            dfs3(hson[u],u);
        }
        f[u][0]=1;
        ans+=g[u][0];
        for(auto v:adj[u]){
            if(v==pre||v==hson[u]) continue;
            f[v]=now;
            now+=len[v]<<1;
            g[v]=now;
            now+=len[v]<<1;
            dfs3(v,u);
            for(int i=0;i<len[v];i++){
                if(i){
                    ans+=f[u][i-1]*g[v][i];
                }
                ans+=g[u][i+1]*f[v][i];
            }
            for(int i=0;i<len[v];i++){
                g[u][i+1]+=f[u][i+1]*f[v][i];
                if(i) g[u][i-1]+=g[v][i];
                f[u][i+1]+=f[v][i];
            }
        }
    }

}using namespace Tree;

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    now=buf;
    f[1]=now;
    now+=len[1]<<1;
    g[1]=now;
    now+=len[1]<<1;
    dfs3(1,0);
    cout<<ans;

    return 0;
}
