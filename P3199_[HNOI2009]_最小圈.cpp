#include<bits/stdc++.h>
#define double long double
using namespace std;
constexpr int MN=1e6+15,ME=520,INF=0x3f3f3f3f;
constexpr double eps=1e-10;
struct Edge{
    int v;
    double w;
    int id;
};
int sum,n,m,ans,dg[MN],S=MN-3,T=MN-2,u[MN],v[MN],cur[MN],dep[MN];
bool vis[MN];
vector<Edge> adj[MN];

void add(int u,int v,double w){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,vs});
    adj[v].push_back({u,0,us});
}

bool bfs(){
    memset(dep,-1,sizeof(dep));
    dep[S]=0;
    queue<int> q;
    q.push(S);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto e:adj[u]){
            if(e.w&&dep[e.v]==-1){
                dep[e.v]=dep[u]+1;
                q.push(e.v);
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dep[T]!=-1);
}

double dfs(int u,double lim){
    if(u==T) return lim;
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&adj[u][i].w){
            double p=dfs(v,min(lim,adj[u][i].w));
            if(p){
                adj[u][i].w-=p;
                adj[v][adj[u][i].id].w+=p;
                return p;
            }else dep[v]=-1;
        }
    }
    return 0;
}

double dinic(){
    double ans=0,flow;
    while(bfs()){
        while(flow=dfs(S,INF)) ans+=flow;
    }
    return ans;
}

void init(){
    adj[S].clear();
    adj[T].clear();
    for(int i=1;i<=n;i++){
        adj[i].clear();
    }
}

bool check(int k){
    init();
    for(int i=1;i<=n;i++){
        add(S,i,m);
        add(i,T,m+k+k-dg[i]);
    }
    for(int i=1;i<=m;i++){
        add(u[i],v[i],1);
        add(v[i],u[i],1);
    }
    return n*m-dinic()>eps;
}

void dfs(int u){
    vis[u]=1;
    ++ans;
    for(auto e:adj[u]){
        if(e.w>eps&&!vis[e.v]) dfs(e.v);
    }
}

int main(){
    while(cin>>n>>m){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            dg[i]=0;
        }
        for(int i=1;i<=m;i++){
            cin>>u[i]>>v[i];
            dg[u[i]]++;
            dg[v[i]]++;
        }
        if(!m) {puts("1\n1");continue;}
        double l=0,r=m;
        while(r-l>1.0/n/n){
            double mid=(l+r)/2;
            if(check(mid)) l=mid;
            else r=mid;
        }
        check(l);
        ans=0;
        dfs(S);
        cout<<ans-1<<'\n';
        for(int i=1;i<=n;i++){
            if(vis[i]) cout<<i<<'\n';
        }
    }
    return 0;
}
