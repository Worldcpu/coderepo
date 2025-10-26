#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
};
int n,m,ctot,hb;
vector<Edge> adj[MN];
vector<int> ans;

namespace Tree{
    int cf[MN],dep[MN],fa[MN];
    bool vis[MN],col[MN],vise[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        vis[u]=1;
        dep[u]=dep[pre]+1;
        col[u]=col[pre]^1;
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(v==pre) continue;
            if(!vis[v]){
                vise[id]=1;
                dfs1(v,u);
            }else if(!vise[id]){
                vise[id]=1;
                if(col[u]==col[v]){
                    hb=e.id;
                    ctot++;
                    cf[u]++,cf[v]--;
                }else cf[u]--,cf[v]++;
            }
        }
    }

    void dfs2(int u){
        vis[u]=1;
        for(auto e:adj[u]){
            if(!vis[e.v]){
                dfs2(e.v);
                if(cf[e.v]==ctot){
                    ans.push_back(e.id);
                }
                cf[u]+=cf[e.v];
            }
        }
    }

}using namespace Tree;

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]) dfs1(i,0);
    }
    if(!ctot){
        cout<<m<<'\n';
        for(int i=1;i<=m;i++){
            cout<<i<<' ';
        }
        return 0;
    }
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        if(!vis[i]) dfs2(i);
    }
    if(ctot==1) ans.push_back(hb);
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<'\n';
    for(auto p:ans) cout<<p<<' ';
    

    return 0;
}