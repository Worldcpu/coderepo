#include<iostream>
#include<vector>
using namespace std;
const int MN=2e4+15,ME=1e5+15;
int root,n,m,dfn[MN],low[MN],cnt;
vector<int> adj[MN];
bool iscut[MN];
void tarjan(int u){
    int child=0;
    low[u]=dfn[u]=++cnt;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!dfn[v]){
            tarjan(v);
            if(u==root){
                child++;
            }
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]&&u!=root){
                iscut[u]=1;
            }
        }else low[u]=min(low[u],dfn[v]);
    }
    if(u==root&&child>=2){
        iscut[u]=1;
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            root=i;
            tarjan(i);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(iscut[i]) ans++;
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++){
        if(iscut[i]){
            cout<<i<<" ";
        }
    }
    return 0;
}