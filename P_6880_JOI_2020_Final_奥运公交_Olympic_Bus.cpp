#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520+15,ME=2e5+15,INF=1e9;
struct EdgeN{
    int u,v,w,w2,id;
}e[ME];
struct Edge{
    int v,w,w2,id;
};
int n,m,ans=INF;
vector<Edge> adj[MN];

namespace Dijkstra{
    int dis[MN][MN],tag[ME],col[ME];
    bool vis[MN],vise[ME];

    void init(int st){
        for(int i=1;i<=n;i++){
            dis[st][i]=INF;
            vis[i]=0;
        }
        dis[st][st]=0;
    }

    void dijk(int st,int op){
        init(st);
        for(int i=1;i<=n;i++){
            int u=0,disu=INF;
            for(int j=1;j<=n;j++){
                if(dis[st][j]<disu&&!vis[j]){
                    disu=dis[st][j];
                    u=j;
                }
            }
            if(!u) break;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w,w2=e.w2,id=e.id;
                if(!vise[id]) continue;
                if(dis[st][v]>dis[st][u]+w){
                    dis[st][v]=dis[st][u]+w;
                    if(!op) tag[v]=id;
                }
            }
        }
        if(!op){
            for(int i=1;i<=n;i++){
                col[tag[i]]=1;
            }
        }
    }

}using namespace Dijkstra;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w,d;
        cin>>u>>v>>w>>d;
        adj[u].push_back({v,w,d,i<<1});
        adj[v].push_back({u,w,d,i<<1|1});
        vise[i<<1]=1;
        e[i]={u,v,w,d,i};
    }
    dijk(1,0);
    dijk(n,0);
    for(int i=2;i<n;i++) dijk(i,1);
    ans=min(ans,dis[1][n]+dis[n][1]);
    cerr<<dis[1][n]<<' '<<dis[n][1]<<'\n';
    for(int i=1;i<=m;i++){
        if(col[i<<1]) continue;
        auto eg=e[i];
        int d1=min(dis[1][n],dis[1][eg.v]+eg.w+dis[eg.u][n]),d2=min(dis[n][1],dis[n][eg.v]+eg.w+dis[eg.u][1]);
        ans=min(ans,d1+d2+eg.w2);
    }
    for(int i=1;i<=m;i++){
        if(!col[i<<1]) continue;
        vise[i<<1]=0,vise[i<<1|1]=1;
        dijk(1,1),dijk(n,1);
        ans=min(ans,dis[1][n]+dis[n][1]+e[i].w2);
        vise[i<<1]=1,vise[i<<1|1]=0;
    }
    if(ans<INF) cout<<ans;
    else cout<<-1;

    return 0;
}