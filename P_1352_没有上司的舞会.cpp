#include<iostream>
#include<vector>
using namespace std;
const int MN=6e3+15;
int n,h[MN],f[MN][2];
vector<int> adj[MN];
void dfs(int u){
    f[u][0]=0;
    f[u][1]=h[u];
    for(auto v:adj[u]){
        dfs(v);
        f[u][0]+=max(f[v][0],f[v][1]);
        f[u][1]+=f[v][0];
    }
}
bool awa[MN];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        awa[u]=1;
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(awa[i]==0){
            dfs(i);
            cout<<max(f[i][0],f[i][1]);
            break;
        }
    }
    return 0;
}