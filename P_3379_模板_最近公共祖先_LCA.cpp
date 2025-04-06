#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int MN=5e5+15,ML=40;
int n,m,s;
vector<int> adj[MN];
int fa[MN][ML],dep[MN],ml;
void dfs(int u,int pre){
    dep[u]=dep[pre]+1;
    fa[u][0]=pre;
    for(int i=1;i<=ml;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(auto v:adj[u]){
        if(v!=pre){
            dfs(v,u);
        }
    }
}
int lca(int x,int y){
    if(dep[x]>dep[y]) swap(x,y);
    for(int i=20;i>=0;i--){
        if(dep[fa[y][i]]>=dep[x]){
            y=fa[y][i];
        }
    }
    if(x==y) return x;
    for(int i=__lg(dep[x]);i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int main(){
    cin>>n>>m>>s;
    ml=__lg(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(s,0);
    while (m--)
    {
        int u,v;
        cin>>u>>v;
        cout<<lca(u,v)<<endl;
    }
    
    return 0;
}