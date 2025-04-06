#include<iostream>
#include<cstring>
#include<vector>
#define int long long
using namespace std;
const int MD=1e6+15;
int n;
int p[MD],maxx;
bool vis[MD];
vector<int> adj[MD];
bool match(int id,int u){
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!vis[v]){
            vis[v]=1;
            if(!p[v]||match(id,p[v])){
                p[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v,ki=i+10000;
        cin>>u>>v;
        adj[u].push_back(ki);
        adj[ki].push_back(u);
        adj[v].push_back(ki);
        adj[ki].push_back(v);
    }
    int ans=0;
    for(int i=1;i<=10000;i++){
        memset(vis,0,sizeof(vis));
        if(!match(i,i)){
            cout<<i-1;
            return 0;
        }else ans++;
    }
    cout<<ans;
    return 0;
}