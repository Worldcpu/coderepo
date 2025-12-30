#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=520,INF=0x3f3f3f3f3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
int n,m,q,Ton,a[MN],b[MN],ecnt,ew[MN],lstans;
pir e[MN];

namespace WLL{
struct Edge{
    int v,w,c,id;
};
int S,T,mincst,dis[MN],cur[MN];
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
    memset(dis,128,sizeof(dis));
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
    return (dis[T]>=-INF);
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
    mincst=0;
    while(spfa()){
        ans+=dfs(S,INF);// 这里和最大流的dinic不太一样，注意一下。
    }
    return ans;
}

    void init(){
        S=n+m+2,T=n+m+3;
        for(int i=0;i<=T;i++){
            adj[i].clear();
        }
        for(int i=1;i<=ecnt;i++){
            add(e[i].first,e[i].second+m,1,ew[i]);
        }
        for(int i=0;i<m;i++){
            add(S,i,1,0);
            // cerr<<S<<' '<<i<<' '<<1<<' '<<0<<'\n';
        }
        for(int i=0;i<n;i++){
            add(i+m,T,1,0);
            // cerr<<i+m<<' '<<T<<' '<<1<<' '<<0<<'\n';
        }
    }

}

void sol(){
    WLL::init();
    WLL::dinic();
    lstans=WLL::mincst;
    cout<<WLL::mincst<<'\n';
}

signed main(){
    cin>>m>>n>>Ton;
    for(int i=0;i<m;i++){
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        cin>>b[i];
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(min((j-a[i]+n)%n,(a[i]-j+n)%n)==b[i]){
                e[++ecnt]=pir(i,j);
            }
        }
    }

    for(int i=1;i<=ecnt;i++){
        cin>>ew[i];
    }   
    sol();

    cin>>q;
    while(q--){
        int x,v;
        cin>>x>>v;
        x=x-lstans*Ton,v=v-lstans*Ton;
        ew[x]=v;
        sol();
    }
    return 0;
}