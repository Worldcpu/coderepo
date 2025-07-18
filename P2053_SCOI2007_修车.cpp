#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e3+15;
constexpr int INF=0x3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
int n,m,S=MN-3,T=MN-2,mincst,dis[MN],cur[MN],a[MN][MN];
vector<Edge> adj[MN];
bool vis[MN];

void add(int u,int v,int w,int c){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,c,vs});
    adj[v].push_back({u,0,-c,us});
}

bool spfa(){// SPFA,有后遗症的自行替换
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
            if(e.w&&dis[e.v]>dis[u]+e.c){
                dis[e.v]=dis[u]+e.c;
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
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;// 弧优化
        int v=adj[u][i].v;
        if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].c){
            int p=dfs(v,min(lim,adj[u][i].w));
            if(!p) dis[v]=INF;
            adj[u][i].w-=p;
            adj[v][adj[u][i].id].w+=p;
            ret+=p;
            lim-=p;
            mincst+=p*adj[u][i].c;// mincst在这里计算
            if(!lim) break;
        }
    }
    vis[u]=0;
    return ret;
}

int dinic(){
    int ans=0;
    while(spfa()){
        ans+=dfs(S,INF);// 这里和最大流的dinic不太一样，注意一下。
    }
    return ans;
}

int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        add(S,i,1,0);
        int tmp=n;
        for(int j=1;j<=m;j++){
            for(int k=1;k<=n;k++){
                add(i,++tmp,1,a[i][j]*k);
            }
        }
    }
    int tmp=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            add(++tmp,T,1,0);
        }
    }
    dinic();
    cout<<fixed<<setprecision(2)<<1.0*mincst/n;
    return 0;
}
