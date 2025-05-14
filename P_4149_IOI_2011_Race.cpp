#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e6+15,INF=1e9+7;
struct Edge{
    int v,w;
};
int n,K,sum,rt,ans=INF,tot,del[MN],now[MN],dis[MN],dep[MN],siz[MN],maxp[MN];
vector<Edge> adj[MN];
bool vis[MN];
int judge[MN];

void getp(int u,int fa){
    siz[u]=1;
    maxp[u]=0;
    // dep[u]=dep[fa]+1;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa||vis[v]) continue;
        getp(v,u);
        siz[u]+=siz[v];
        maxp[u]=max(maxp[u],siz[v]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt]) rt=u;
}

void getdep(int u,int fa){
    for(auto e:adj[u]){
        if(e.v==fa||vis[e.v]) continue;
        dep[e.v]=dep[u]+1;
        getdep(e.v,u);
    }
}

void getdis(int u,int fa){
    now[++now[0]]=u;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[u]+w;
        getdis(v,u);
    }
}

void clac(int u){
    tot=0;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]) continue;
        now[0]=0;
        dis[v]=w;
        getdis(v,u);
        for(int i=now[0];i>=1;i--){
            if(K-dis[now[i]]>=0&&judge[K-dis[now[i]]]) ans=min(ans,dep[now[i]]+dep[judge[K-dis[now[i]]]]-2*dep[u]);
        }
        for(int i=now[0];i>=1;i--){
            if(dis[now[i]]<=K) judge[dis[now[i]]]=now[i],del[++tot]=dis[now[i]];
        }
    }
    for(int i=1;i<=tot;i++) judge[del[i]]=0;
}

void solve(int u){
    vis[u]=1;
    judge[0]=u;
    dep[u]=0;
    getdep(u,0);
    clac(u);
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]) continue;
        sum=siz[v];
        maxp[rt=0]=INF;
        getp(v,0);
        solve(rt);
    }
}

int main(){
    cin>>n>>K;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u++;
        v++;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    maxp[rt]=sum=n;
    getp(1,0);
    solve(rt);
    if(ans==INF) cout<<-1;
    else cout<<ans;
    return 0;
}