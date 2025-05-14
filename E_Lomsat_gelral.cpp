#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,c[MN],cnt[MN],maxx,Son,siz[MN],hson[MN],ans[MN],sum;
vector<int> adj[MN];

void dfs(int u,int fa){
    siz[u]=1;
    for(auto v:adj[u]){
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[hson[u]]<=siz[v]) hson[u]=v;
    }
}

void add(int u,int fa,int k){
    cnt[c[u]]+=k;
    if(cnt[c[u]]>maxx){
        maxx=cnt[c[u]];
        sum=c[u];
    }else if(cnt[c[u]]==maxx){
        sum+=c[u];
    }
    for(auto v:adj[u]){
        if(v==fa||v==Son) continue;
        add(v,u,k);
    }
}

void dsu(int u,int fa,int opt){
    for(auto v:adj[u]){
        if(v==fa||v==hson[u]) continue;
        dsu(v,u,0);
    }
    if(hson[u]) dsu(hson[u],u,1),Son=hson[u];
    add(u,fa,1),Son=0;
    ans[u]=sum;
    if(!opt) add(u,fa,-1),sum=0,maxx=0;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    dsu(1,0,0);
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    return 0;
}