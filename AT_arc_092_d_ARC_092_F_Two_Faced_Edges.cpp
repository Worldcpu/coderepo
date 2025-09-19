#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,MD=2e3+15;
int u[MN],v[MN],pre[MD][MD],suf[MD][MD],n,m;
bool w[MD][MD];
vector<int> adj[MN];

void dfs(int u,bool w[]){
    w[u]=1;
    for(auto v:adj[u]){
        if(w[v]) continue;
        dfs(v,w);
    }
}

void dfs(int u,int p[],int rt){
    p[u]=rt;
    for(auto v:adj[u]){
        if(!p[v]) dfs(v,p,rt);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        adj[u[i]].push_back(v[i]);
    }
    for(int i=1;i<=n;i++){
        dfs(i,w[i]);
        pre[i][i]=suf[i][i]=i;
        for(auto v:adj[i]){
            if(!pre[i][v]) dfs(v,pre[i],v);
        }
        reverse(adj[i].begin(),adj[i].end());
        for(auto v:adj[i]){
            if(!suf[i][v]) dfs(v,suf[i],v);
        }
    }
    for(int i=1;i<=m;i++){
        if(w[v[i]][u[i]]^(pre[u[i]][v[i]]!=suf[u[i]][v[i]])){
            cout<<"diff\n";
        }else cout<<"same\n";
    }
    return 0;
}