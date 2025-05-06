#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
constexpr int MK=50;
constexpr int INF=0x3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
int S=MN-3,T=MN-2,mincst,m,n,tot,dis[MN],cur[MN],a[MK][MK],mp[MK][MK];
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
            if(!lim) break;// 若流量为0则优化
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

void clear(){
    mincst=0;
    adj[S].clear();
    adj[T].clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            adj[mp[i][j]].clear();
            adj[mp[i][j]+tot].clear();
        }
    }
}

void solve1(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            if(i==1) add(S,mp[i][j],1,0);
            add(mp[i][j],mp[i][j]+tot,1,-a[i][j]);
            if(i==n){
                add(mp[i][j]+tot,T,INF,0);
                continue;
            }
            add(mp[i][j]+tot,mp[i+1][j],1,0);
            add(mp[i][j]+tot,mp[i+1][j+1],1,0);
        }
    }
    dinic();
    cout<<-mincst<<'\n';
}

void solve2(){
    clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            if(i==1) add(S,mp[i][j],1,0);
            add(mp[i][j],mp[i][j]+tot,INF,-a[i][j]);
            if(i==n){
                add(mp[i][j]+tot,T,INF,0);
                continue;
            }
            add(mp[i][j]+tot,mp[i+1][j],1,0);
            add(mp[i][j]+tot,mp[i+1][j+1],1,0);
        }
    }
    dinic();
    cout<<-mincst<<'\n';
}

void solve3(){
    clear();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            if(i==1) add(S,mp[i][j],1,0);
            add(mp[i][j],mp[i][j]+tot,INF,-a[i][j]);
            if(i==n){
                add(mp[i][j]+tot,T,INF,0);
                continue;
            }
            add(mp[i][j]+tot,mp[i+1][j],INF,0);
            add(mp[i][j]+tot,mp[i+1][j+1],INF,0);
        }
    }
    dinic();
    cout<<-mincst;
}

int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m+i-1;j++){
            cin>>a[i][j];
            mp[i][j]=++tot;
        }
    }
    // tot=()
    solve1();
    solve2();
    solve3();
    return 0;
}