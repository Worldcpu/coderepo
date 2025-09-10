#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int fa[MN],n,ans;
vector<int> adj[MN];

int dfs(int u,int pre){
    vector<int> vct;
    for(auto v:adj[u]){
        if(v==pre) continue;
        int ret=dfs(v,u);
        vct.push_back(ret);
    }
    if(vct.empty()) return 1;
    int tot=0,mx=0;
    for(auto p:vct){
        tot+=p;
        mx=max(mx,p);
    }
    int ret=min(tot/2,tot-mx);
    ans+=ret;
    return tot-2*ret+1;
}

void init(){
    ans=0;
    for(int i=1;i<=n;i++){
        adj[i].clear();
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        adj[x].push_back(i);
    }
    dfs(1,0);
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
