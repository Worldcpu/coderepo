#include<bits/stdc++.h>
using namespace std;
constexpr int MN=4e4+15,ME=520;
constexpr double INF=1e18;
constexpr double eps=1e-8;
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
    memset(dep,0,sizeof(dep));
    dep[S]=1;
    queue<int> q;
    q.push(S);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto e:adj[u]){
            if(e.w>eps&&!dep[e.v]){
                dep[e.v]=dep[u]+1;
                q.push(e.v);
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dep[T]);
}

double ddfs(int u,double lim){
    if(u==T||lim==0) return lim;
    double used=0;
    for(int &i=cur[u];i<adj[u].size();i++){
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&adj[u][i].w>eps){
            double p=ddfs(v,min(lim,adj[u][i].w));
            if(p){
                adj[u][i].w-=p;
                adj[v][adj[u][i].id].w+=p;
                used+=p;
                lim-=p;
                if(fabs(lim)<eps) break;
            }
        }
    }
    return used;
}

double dinic(){
    double ans=0,flow;
    while(bfs()){
        ans+=ddfs(S,INF);
    }
    return ans;
}

void init(){
    for(int i=0;i<MN;i++) adj[i].clear();
}

bool check(double k){
    init();
    for(int i=1;i<=n;i++){
        add(S,i,m);
        add(i,T,m*1.0+k+k-dg[i]*1.0);
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
        memset(dg,0,sizeof(dg));
        if(!m) {cout<<"1\n1\n\n";continue;}
        for(int i=1;i<=m;i++){
            cin>>u[i]>>v[i];
            dg[u[i]]++;
            dg[v[i]]++;
        }
       
        double l=0,r=m;
        while(r-l>1e-6){
            double mid=(l+r)/2.0;
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
