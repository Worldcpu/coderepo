#include<bits/stdc++.h>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
using namespace std;
constexpr int MN=5e5+15;
constexpr int INF=0x3f3f3f3f;
struct Edge{
    int v,w,cst,id;
};
int n,K,S,T,mincost,dis[MN],cur[MN];
vector<Edge> adj[MN];
bool vis[MN];

int getid(int x,int y){
    return n*(x-1)+y;
}

void add(int u,int v,int w,int cst){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,cst,vs});
    adj[v].push_back({u,0,-cst,us});
}

bool spfa(){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    q.push(S);
    dis[S]=0;
    vis[S]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(auto e:adj[u]){
            if(e.w&&dis[e.v]>dis[u]+e.cst){
                dis[e.v]=dis[u]+e.cst;
                if(!vis[e.v]){
                    q.push(e.v);
                    vis[e.v]=1;
                }
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dis[T]!=INF);
}

int dfs(int u,int lim){
    if(u==T) return lim;
    vis[u]=1;
    int ret=0;
    for(int i=cur[u];i<adj[u].size()&&lim;i++){
        cur[u]=i;
        int v=adj[u][i].v;
        if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].cst){
            int p=dfs(v,min(lim,adj[u][i].w));
            if(!p) dis[v]=INF;
            adj[u][i].w-=p;
            adj[v][adj[u][i].id].w+=p;
            ret+=p;
            lim-=p;
            mincost+=p*adj[u][i].cst;
        }
    }
    vis[u]=0;
    return ret;
}

int dinic(){
    int ans=0;
    while(spfa()){
        ans+=dfs(S,INF);
    }
    return ans;
}

int main(){
    cin>>n>>K;
    S=4*n*n+1;
    T=S+1;
    add(S,ls(getid(1,1)),K,0);
    add(rs(getid(n,n)),T,K,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            x=-x;
            add(ls(getid(i,j)),rs(getid(i,j)),1,x);
            add(ls(getid(i,j)),rs(getid(i,j)),INF,0);
            if(i<n){
                add(rs(getid(i,j)),ls(getid(i+1,j)),INF,0);
            }
            if(j<n){
                add(rs(getid(i,j)),ls(getid(i,j+1)),INF,0);
            }
        }
    }
    dinic();
    cout<<-mincost;
    return 0;
}