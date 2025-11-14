#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,p[MN],d[MN],ans;
bool vis[MN];
vector<int> adj[MN];

void dfs(int u){
    vis[u]=1;
    ans++;
    for(auto v:adj[u]){
        if(vis[v]) continue;
        dfs(v);
    }
}

void init(){
    for(int i=1;i<=n;i++){
        adj[i].clear();
        vis[i]=0;
    }
    ans=0;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>p[i];
        adj[i].push_back(p[i]);
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(!vis[p[x]]){
            dfs(p[x]);
        }
        cout<<ans<<' ';
    }
    cout<<'\n';
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}