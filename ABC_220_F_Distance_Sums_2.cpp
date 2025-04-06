#include<iostream>
#include<vector>
#define ull long long
using namespace std;
const int MN=1e6+15;
vector<int> adj[MN];
ull n,ans[MN],siz[MN],dep[MN];
void dfs1(int u,int fa){
    siz[u]=1;
    dep[u]=dep[fa]+1;
    for(auto v:adj[u]){
        if(fa!=v){
            dfs1(v,u);
            siz[u]+=siz[v];
        }
    }
}
void dfs2(int u,int fa){
    for(auto v:adj[u]){
        if(fa!=v){
            ans[v]=ans[u]+siz[1]-2*siz[v];
            dfs2(v,u);
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++){
        ans[1]+=dep[i];
    }
    dfs2(1,0);
    ull maxx=-1e13,p;
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}