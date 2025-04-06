#include<bits/stdc++.h>
using namespace std;
const int MN=2e5+15;
struct edge{
    int v,id;
    bool fan;
};
vector<edge> adj[MN];
vector<edge> ans;
int t,n,m,du[MN],in[MN],out[MN],cur[MN];
bool vis[MN];

void hierholzer(int u){
    for(int &i=cur[u];i<adj[u].size();i++){
        edge e=adj[u][i];
        if(vis[e.id]) continue;
        vis[e.id]=1;
        hierholzer(e.v);
        ans.push_back(e);
    }
}

void solvend(){
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        adj[u].push_back({v,i,0});
        adj[v].push_back({u,i,1});
        du[u]++;
        du[v]++;
    }
    if(m==0){
        cout<<"YES";
        return;
    }
    for(int i=1;i<=n;i++){
        if(du[i]&1){
            cout<<"NO";
            return;
        }
    }
    
    hierholzer(u);
    if(ans.size()<m){
        cout<<"NO";
        return;
    }
    else cout<<"YES\n";
    for(int i=ans.size()-1;i>=0;i--){
        // cout<<ans[i].id<<" ";
        ans[i].fan ? cout<<'-'<<ans[i].id<<" " : cout<<ans[i].id<<" ";
    }
}
void solved(){
    int u,v;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        adj[u].push_back({v,i,0});
        in[v]++;
        out[u]++;
    }
    if(m==0){
        cout<<"YES";
        return;
    }
    for(int i=1;i<=n;i++){
        if(in[i]!=out[i]){
            cout<<"NO";
            return;
        }
    }
    hierholzer(u);
    if(ans.size()<m){
        cout<<"NO";
        return;
    }
    else cout<<"YES\n";
    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i].id<<" ";
    }

}
int main(){
    cin>>t>>n>>m;
    if(t==1) solvend();
    else solved();
    return 0;
}