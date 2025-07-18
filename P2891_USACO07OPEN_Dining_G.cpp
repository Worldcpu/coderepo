#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MK=520,INF=0x3f3f3f3f;
struct Edge{
    int v,w,id;
};
int S=MN-3,T=MN-2,cur[MN],dep[MN],n,f,d;
vector<Edge> adj[MN];

void add(int u,int v,int w){
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

int dfs(int u,int lim){
    if(u==T) return lim;
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&adj[u][i].w){
            int p=dfs(v,min(lim,adj[u][i].w));
            if(p){
                adj[u][i].w-=p;
                adj[v][adj[u][i].id].w+=p;
                return p;
            }else dep[v]=-1;
        }
    }
    return 0;
}

int dinic(){
    int ans=0,flow;
    while(bfs()){
        while(flow=dfs(S,INF)) ans+=flow;
    }
    return ans;
}

int main(){
    cin>>n>>f>>d;
    for(int i=1;i<=f;i++){
        add(S,i+1,1);
    }
    for(int i=1;i<=d;i++){
        add(1+f+i+n,T,1);
    }
    for(int i=1;i<=n;i++){
        add(1+f+i,1+f+n+d+1+i,1);
    }
    for(int i=1;i<=n;i++){
        int x,y,z;
        cin>>x>>y;
        for(int j=1;j<=x;j++){
            cin>>z;
            add(1+z,1+f+i,1);
        }
        for(int j=1;j<=y;j++){
            cin>>z;
            add(1+f+n+d+1+i,1+f+n+z,1);
        }
    }
   cout<<dinic();
    return 0;
}
