#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=4e5+15;
constexpr ll INF=1e18;
struct Edge{
    int v;
    ll len;
    int id;
};
struct STOEdge{
    int u,v;
    ll w;
    int id;
}e[MN];
int n,m,t,S,T,tot,etot,top,dcc,dfn[MN],low[MN],col[MN],st[MN],dep[MN],cur[MN];
vector<Edge> adj[MN];
vector<int> G[MN];
bool vis[MN],isok[MN];

void add(int u,int v,int w,int id){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,vs});
    adj[v].push_back({u,0,us});
    e[++etot]={u,v,w,id};
    e[++etot]={v,u,0,id};
}

bool bfs(){
    memset(dep,-1,sizeof(dep));
    queue<int> q;
    q.push(S);
    dep[S]=0;
    while (!q.empty())
    {
        int f=q.front();
        q.pop();
        for(auto e:adj[f]){
            int v=e.v,len=e.len;
            if(dep[v]==-1&&len){
                dep[v]=dep[f]+1;
                q.push(v);
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dep[T]!=-1);
}
ll dfs(int u,ll limit){
    if(u==T) return limit;
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&adj[u][i].len){
            int p=dfs(v,min(adj[u][i].len,limit));
            if(p){
                adj[u][i].len-=p;
                adj[v][adj[u][i].id].len+=p;
                return p;
            }else dep[v]=-1;
        }
    }
    return 0;
}
ll dinic(){
    ll ans=0,flow;
    while (bfs())
    {
        while (flow=dfs(S,INF)){
            ans+=flow;
        }
    }
    return ans;
}

void tarjan(int u){
    low[u]=dfn[u]=++tot;
    st[++top]=u;
    vis[u]=1;
    for(auto v:G[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        int p;
        dcc++;
        do
        {
            p=st[top--];
            col[p]=dcc;
            vis[p]=0;
        } while (p!=u);
    }
}

int main(){
    cin>>n>>m>>t;
    S=n+m+1;
    T=S+1;
    for(int i=1;i<=n;i++){
        add(S,i,1,0);
    }
    for(int i=1;i<=m;i++){
        add(i+n,T,1,0);
    }
    for(int i=1;i<=t;i++){
        int u,v;
        cin>>u>>v;
        add(u,v+n,1,i);
    }
    dinic();
    for(int i=1;i<=T;i++){
        for(auto e:adj[i]){
            if(e.len>0){
                G[i].push_back(e.v);
            }
        }
    }
    for(int i=1;i<=T;i++){
        if(!dfn[i]) tarjan(i);
    }
    int ret=0;
    for(int i=1;i<=etot;i++){
        if(e[i].w==1&&(i%2!=0)){
            if(e[i].u==S||e[i].u==T||e[i].v==S||e[i].v==T) continue;
            if(col[e[i].u]!=col[e[i].v]){
                ret++;
                isok[e[i].id]=1;
            }
        }
    }
    cout<<ret<<'\n';
    for(int i=1;i<=t;i++){
        if(isok[i]) cout<<i<<" ";
    }
    return 0;
}