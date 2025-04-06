#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15,INF=1e9;
int n,m,siz[MN],maxp[MN],sum,dis[MN],rem[MN],rt,res;
bool vis[MN];
struct edge
{
    int v,w;
};
vector<edge> adj[MN];
bool cmp(int x,int y){
    return dis[x]<dis[y];
}
void dfs(int u,int fa){
    siz[u]=1;
    maxp[u]=0;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]||v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        maxp[u]=max(maxp[u],siz[v]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt]) rt=u;
}

void getdis(int u,int fa){
    rem[++rem[0]]=u;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[u]+w;
        getdis(v,u);
    }
}

int clac(int u,int w){
    rem[0]=0;
    dis[u]=w;
    getdis(u,0);
    sort(rem+1,rem+rem[0]+1,cmp);
    int l=1,r=rem[0],ans=0;
    while (l<=r){
        if(dis[rem[l]]+dis[rem[r]]<=m){
            ans+=r-l;
            l++;
        }else r--;
    }
    return ans;
}

void solve(int u){
    vis[u]=1;
    res+=clac(u,0);
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]) continue;
        res-=clac(v,w);
        sum=siz[v];
        rt=0;
        maxp[rt]=INF;
        dfs(v,u);
        solve(rt);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    cin>>m;
    maxp[rt]=sum=n;
    dfs(1,0);
    solve(rt);
    cout<<res;
    return 0;
}