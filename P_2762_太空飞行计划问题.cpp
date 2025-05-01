#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,INF=0x3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
int n,m,cst[MN],S,T,cur[MN],dis[MN],pay[MN],mincst;
vector<Edge> adj[MN];
bool vis[MN];
void add(int u,int v,int w,int c){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,c,vs});
    adj[v].push_back({u,0,c,us});
}

bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    dis[S]=0;
    q.push(S);
    vis[S]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(auto e:adj[u]){
            if(e.w&&dis[e.v]>dis[u]+e.c){
                dis[e.v]=dis[u]+e.c;
                if(!vis[e.v]){
                    vis[e.v]=1;
                    q.push(e.v);
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
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;
        int v=adj[u][i].v;
        if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].c){
            int p=dfs(v,min(lim,adj[u][i].w));
            if(p){
                adj[u][i].w-=p;
                adj[v][adj[u][i].id].w+=p;
                lim-=p;
                ret+=p;
                mincst+=p*adj[u][i].c;
                if(!lim) break;
            }else dis[v]=INF;
        }
    }
    return ret;
}

int dinic(){
    int ans=0,flow;
    while(spfa()){
        while(flow=dfs(S,INF)) ans+=flow;
    }
    return ans;
}

void input(int i){
    string ln;
    getline(cin,ln);
    istringstream in(ln);
    in>>pay[i];
    int cur;
    // cout<<pay[i]<<" \n";
    while(in>>cur){
        add(i,m+cur,INF,0);
    }
}

int main(){
    cin>>m>>n;
    getchar();
    for(int i=1;i<=m;i++){
        input(i);
    }
    for(int i=1;i<=n;i++){
        cin>>cst[i];
    }
    S=MN-3;
    T=S+1;
    for(int i=1;i<=m;i++){
        add(S,i,pay[i],0);
    }
    for(int i=1;i<=n;i++){
        add(m+i,T,cst[i],0);
    }
    int mxflow=dinic();
    for(int i=1;i<=m;i++){
        if(dis[i]) cout<<i<<" ";
    }
    cout<<'\n';
    for(int i=1;i<=n;i++){
        if(dis[i+m]) cout<<i<<" ";
    }
    cout<<'\n'<<mxflow;
    return 0;
}