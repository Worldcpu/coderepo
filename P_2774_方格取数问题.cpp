#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MK=520,INF=0x3f3f3f3f;
struct Edge{
    int v,w,id;
};
int fx[4]={1,-1,0,0},fy[4]={0,0,1,-1};
int S=MN-3,T=MN-2,m,n,tot,cur[MN],dep[MN],a[MK][MK],mp[MK][MK],sum;
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
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            sum+=a[i][j];
            mp[i][j]=++tot;
            if((i+j)&1){
                add(S,mp[i][j],a[i][j]);
            }else add(mp[i][j],T,a[i][j]);
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if((i+j)&1){
                for(int k=0;k<4;k++){
                    int nx=i+fx[k],ny=j+fy[k];
                    if(nx<=0||nx>m||ny<=0||ny>n) continue;
                    add(mp[i][j],mp[nx][ny],INF);
                }
            }
        }
    }
    cout<<sum-dinic();
    return 0;
}