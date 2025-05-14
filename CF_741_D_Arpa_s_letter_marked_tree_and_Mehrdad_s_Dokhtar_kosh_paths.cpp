#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,MK=(1<<22),INF=1e9;
struct Edge{
    int v;
    int w;
};
int n,Son,f[MK],num[MN],ans[MN],siz[MN],hson[MN],cnt[MK];
vector<Edge> adj[MN];

void dfs(int u,int fa){
    siz[u]=1;
    ans[u]=-INF;
    for(auto e:adj[u]){
        if(e.v==fa) continue;
        num[e.v]^=num[u];
        dfs(e.v,u);
        siz[u]+=siz[e.v];
        if(siz[hson[u]]<siz[e.v]) hson[u]=e.v;
    }
}

void add(int u,int fa,int k){

}

void dsu(int u,int fa,int opt){
    for(auto e:adj[u]){
        if(e.v==fa||e.v==hson[u]) continue;
        dsu(e.v,u,0);
        ans[u]=max(ans[u],ans[e.v]);
    }
    if(hson[u]) dsu(hson[u],u,1),Son=hson[u];
    add(u,fa,1),Son=0;
    ans[u]
}

int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        int u;
        char w;
        cin>>u>>w;
        adj[u].push_back({i,w-'a'});
        adj[i].push_back({u,w-'a'});
        num[i]=1<<(w-'a');
    }
    dfs(1,0);
    memset()
    dsu(1,1,0);
    return 0;
}