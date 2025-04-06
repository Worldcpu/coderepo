#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int n,m;
const int MN=5e4+15,ML=40;
int fa[MN][ML],dep[MN],ml,sum[MN],ans=-1;
vector<int> adj[MN];
void dfs(int u,int pre){
    fa[u][0]=pre;
    dep[u]=dep[pre]+1;
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
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    for(int i=ML-1;i>=0;i--){
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
void dfss(int u,int fa){
    for(auto v:adj[u]){
        if(v!=fa){
            dfss(v,u);
            sum[u]+=sum[v];
        }
    }
    ans=max(ans,sum[u]);
}
int main(){
    cin>>n>>m;
    ml=__lg(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    while (m--)
    {
        int s,t;
        cin>>s>>t;
        int l=lca(s,t);
        sum[s]++;
        sum[t]++;
        sum[l]--;
        if(l!=1){
            sum[fa[l][0]]--;
        }
    }
    dfss(1,0);
    cout<<ans;
    return 0;
}