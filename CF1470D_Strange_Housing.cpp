#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,fa[MN],pre[MN];
bool col[MN];
vector<int> adj[MN];

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void dfs(int u,int pre){
    fa[u]=pre;
    for(auto v:adj[u]){
        if(v==pre||fa[v]) continue;
        dfs(v,u);
    }
}

void dfss(int u,int pre){
    bool flag=1;
    for(auto v:adj[u]){
        if(col[v]) flag=0;
    }
    if(flag) col[u]=1;
    for(auto v:adj[u]){
        if(fa[v]==u) dfss(v,u);
    }
}

void init(){
    for(int i=0;i<=n;i++) pre[i]=i,adj[i].clear(),fa[i]=col[i]=0;
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        pre[root(u)]=root(v);
    }
    for(int i=1;i<=n;i++){
        if(root(1)!=root(i)){
            cout<<"NO\n";
            return;
        }
    }
    fa[1]=1;
    dfs(1,1),dfss(1,1);
    cout<<"YES\n";
    int ret=0;
    for(int i=1;i<=n;i++){
        ret+=col[i];   
    }
    cout<<ret<<'\n';
    for(int i=1;i<=n;i++){
        if(col[i]) cout<<i<<" ";
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
