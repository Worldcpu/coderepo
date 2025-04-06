#include<iostream>
#include<vector>
using namespace std;
const int MN=5e5+15,ME=2e6+16;
int n,m,cnt,dfn[MN],low[MN],edcc;
struct edge
{
    int v,id;
};
bool gb[ME],vis[MN];
vector<edge> adj[MN];
vector<int> ans[MN];
void tarjan(int u,int fa){
    low[u]=dfn[u]=++cnt;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i].v;
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                gb[adj[u][i].id]=1;
            }
        }else if(v!=fa) low[u]=min(low[u],dfn[v]);
    }
}
void dfs(int u){
    vis[u]=1;
    if(u) ans[edcc].push_back(u);

    for(int i=0;i<adj[u].size();i++){
        if(gb[adj[u][i].id]||vis[adj[u][i].v]){
            continue;
        }
        dfs(adj[u][i].v);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(u==v) continue;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            edcc++;
            dfs(i);
        }
    }
    cout<<edcc<<endl;
    for(int i=1;i<=edcc;i++){
        cout<<ans[i].size()<<" ";
        for(int j=0;j<ans[i].size();j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}