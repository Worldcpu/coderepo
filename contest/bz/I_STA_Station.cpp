#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n;
vector<int> adj[MN];

namespace Tree{
    int siz[MN],dep[MN],ans[MN];


    void dfs1(int u,int pre){
        siz[u]=1;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v]; 
        }
    }

    void dfs2(int u,int pre){
        for(auto v:adj[u]){
            if(v==pre) continue;
            ans[v]=ans[u]+siz[1]-2*siz[v];
            dfs2(v,u);
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
    for(int i=1;i<=n;i++){
        ans[1]+=dep[i];
    }
    dfs2(1,0);
    cout<<(max_element(ans+1,ans+1+n)-ans)<<'\n';
    return 0;
}