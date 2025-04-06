#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15;
const int INF=1e9;
int n,m,query[MN],sum,siz[MN],dis[MN],maxp[MN],rt;
int s[MN],top,rem[MN];
bool test[MN],judge[MN],vis[MN];
struct edge
{
    int v,w;
};
vector<edge> adj[MN];
void dfs(int u,int fa){
    //siz即子树大小，maxp即最大子树大小
    siz[u]=1;
    maxp[u]=0;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa||vis[v]) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        maxp[u]=max(maxp[u],siz[v]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    //考虑与u相邻节点子树的大小
    if(maxp[u]<maxp[rt]) rt=u;
}

void getdis(int u,int fa){
    rem[++rem[0]]=dis[u];
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[u]+w;
        getdis(v,u);
    }
}

void clac(int u){
    int p=0;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]) continue;
        rem[0]=0,dis[v]=w;
        getdis(v,u);
        for(int i=rem[0];i>=1;i--){
            for(int j=1;j<=m;j++){
                if(query[j]>=rem[i]){
                    test[j]|=judge[query[j]-rem[i]];
                }
            }
        }
        for(int i=rem[0];i>=1;i--){
            s[++p]=rem[i];
            judge[rem[i]]=1;
        }
    }
    for(int i=1;i<=p;i++){
        judge[s[i]]=0;
    }
}

void solve(int u){
    vis[u]=1;
    judge[0]=1;
    clac(u);
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]) continue;
        sum=siz[v];
        maxp[rt=0]=INF;
        dfs(v,0);
        solve(rt);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    for(int i=1;i<=m;i++){
        cin>>query[i];
    }
    maxp[rt]=sum=n;
    dfs(1,0);
    solve(rt);

    for(int i=1;i<=m;i++){
        if(test[i]) cout<<"AYE\n";
        else cout<<"NAY\n";
    }
    return 0;
}