#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
    
    friend bool operator<(const Edge &x,const Edge &y){
        return x.v<y.v;
    }
};
int n,m,cur[MN],mnid=1e9;
bool vis[MN];
vector<Edge> adj[MN];
vector<int> ans;

void dfs(int u){
    for(int &i=cur[u];i<adj[u].size();i++){
        int v=adj[u][i].v;
        if(!vis[adj[u][i].id]){
            vis[adj[u][i].id]=1;
            dfs(v);
        }
    }
    ans.push_back(u);
}


int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
        mnid=min({mnid,u,v});
    }
    for(int i=1;i<=500;i++){
        sort(adj[i].begin(),adj[i].end());
    }
    for(int i=1;i<=500;i++){
        if(adj[i].size()&1){
            dfs(i);
            break;
        }
    }
    if(!ans.size()){
        dfs(mnid);
    }
    reverse(ans.begin(),ans.end());
    for(auto p:ans) cout<<p<<'\n';

    return 0;
}