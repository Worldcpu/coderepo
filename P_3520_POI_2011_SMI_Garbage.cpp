#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
};
int n,m;
vector<vector<int>> ans;
vector<Edge> adj[MN];

namespace Euler{
    int cur[MN],st[MN],top;
    bool vise[MN],isin[MN];

    void dfs(int u){
        for(int &i=cur[u];i<adj[u].size();i++){
            if(!vise[adj[u][i].id]){
                vise[adj[u][i].id]=1;
                dfs(adj[u][i].v);
            }
        }
        if(isin[u]){
            vector<int> ret;
            ret.push_back(u);
            while(st[top]!=u){
                isin[st[top]]=0;
                ret.push_back(st[top--]);
            }
            ret.push_back(u);
            ans.push_back(ret);
        }else st[++top]=u,isin[u]=1;
    }

}using namespace Euler;


int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,s,t;
        cin>>u>>v>>s>>t;
        if(s==t) continue;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    for(int i=1;i<=n;i++){
        if(adj[i].size()&1){
            cout<<"NIE\n";
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(Euler::cur[i]!=adj[i].size()){
            isin[st[1]]=0;
            top=0;
            dfs(i);
        }
    }
    cout<<ans.size()<<'\n';
    for(auto p:ans){
        cout<<p.size()-1<<' ';
        for(auto q:p){
            cout<<q<<' ';
        }
        cout<<'\n';
    }
    

    return 0;
}