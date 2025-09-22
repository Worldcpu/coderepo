#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
struct Edge{
    int v,w,id;
};
struct EEdge{
    int u,v,w1,w2;
}e[MN];
int n,m,S,T,mxw,dg[MN],st[MN],top;
vector<int> ans;
vector<Edge> adj[MN],G[MN];

namespace Dinic{
    int dep[MN],cur[MN];

    void initflow(){
        S=0,T=n+m+1;
        for(int i=0;i<=T;i++){
            adj[i].clear();
        }
    }

    void add(int u,int v,int w){
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,w,vs});
        adj[v].push_back({u,0,us});
    }

    bool bfs(int S,int T){
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

    int dfs(int u,int lim,int T){
        if(u==T) return lim;
        for(int i=cur[u];i<adj[u].size();i++){
            cur[u]=i;
            int v=adj[u][i].v;
            if(dep[v]==dep[u]+1&&adj[u][i].w){
                int p=dfs(v,min(lim,adj[u][i].w),T);
                if(p){
                    adj[u][i].w-=p;
                    adj[v][adj[u][i].id].w+=p;
                    return p;
                }else dep[v]=-1;
            }
        }
        return 0;
    }
            
    int dinic(int S,int T){
        int ans=0,flow;
        while(bfs(S,T)){
            while(flow=dfs(S,INF,T)) ans+=flow;
        }
        return ans;
    }
}using namespace Dinic;

namespace Euler{
    int ecur[MN];
    bool evise[MN];

    void dfs(int u){
        while(ecur[u] < (int)G[u].size()){
            Edge &E = G[u][ ecur[u]++ ];
            if(!evise[E.id]){
                evise[E.id] = 1;
                dfs(E.v);
                st[++top] = E.id;
            }
        }
    }
} // 不使用 `using namespace Euler;`

bool check(int k){
    initflow();
    for(int i=1;i<=n;i++){
        add(i+m,T,dg[i]>>1);
    }
    for(int i=1;i<=m;i++){
        add(S,i,1);
        if(e[i].w1<=k){
            add(i,e[i].u+m,1);
        }
        if(e[i].w2<=k) add(i,e[i].v+m,1);
    }
    return dinic(S,T)==m;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w1>>e[i].w2;
        mxw=max({mxw,e[i].w1,e[i].w2});
        dg[e[i].u]++;
        dg[e[i].v]++;
    }
    for(int i=1;i<=n;i++){
        if(dg[i]&1){
            cout<<"NIE\n";
            return 0;
        }
    }
    int l=1,r=1000;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    check(l);
    cout<<l<<'\n';
    for(int i=1;i<=m;i++){
        for(auto ee:adj[i]){
            int v=ee.v;
            if(ee.v==S||ee.w) continue;
            int x=e[i].u,y=e[i].v;
            if(v-m!=y) swap(x,y);
            G[x].push_back({y,0,i});
        }
    }
    Euler::dfs(1);
    for(int i=1;i<=top;i++) cout<<st[i]<<' ';

    return 0;
}