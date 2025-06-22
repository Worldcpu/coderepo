#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MK=520,INF=1e9;
constexpr double eps=1e-10;
struct Edge{
    int v,w;
    double c;
    int id;
};
int n,m,S=MN-3,T=MN-2,a[MK][MK],b[MK][MK],cur[MN],dep[MN];
double dis[MN],mincst;
bool vis[MN];
vector<Edge> adj[MN];

void add(int u,int v,int w,double c){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,c,vs});
    adj[v].push_back({u,0,-c,us});
}

bool spfa(){// SPFA,有后遗症的自行替换
    queue<int> q;
    memset(vis,0,sizeof(vis));
    for(int i=0;i<MN;i++){
        dis[i]=-INF;
    }
    q.push(S);
    dis[S]=0;
    vis[S]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(auto e:adj[u]){
            if(e.w&&dis[e.v]<dis[u]+e.c){
                dis[e.v]=dis[u]+e.c;
                if(!vis[e.v]){
                    q.push(e.v);
                    vis[e.v]=1;
                }
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dis[T]!=-INF);
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
    mincst=0;
    int ans=0;
    while(spfa()){
        ans+=dfs(S,INF);// 这里和最大流的dinic不太一样，注意一下。
    }
    return ans;
}

void init(){
    adj[S].clear();
    adj[T].clear();
    for(int i=1;i<=n;i++){
        adj[i].clear();
        adj[i+n].clear();
    }
}

bool check(double mid){
    init();
    for(int i=1;i<=n;i++){
        add(S,i,1,0);
        add(i+n,T,1,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            add(i,j+n,1,(a[i][j]-b[i][j]*mid));
        }
    }
    dinic();
    return mincst>=eps;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>b[i][j];
        }
    }
    double l=0,r=1e9;
    while(r-l>eps){
        double mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    cout<<fixed<<setprecision(6)<<l;
    return 0;
}
