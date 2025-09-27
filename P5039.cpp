#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f;
int n,m,lab,x[MN],y[MN],d[MN];

namespace FYDinic{
    struct Edge{
        int v,w,c,id;
    };
    int cur[MN],dis[MN],mncst;
    bool vis[MN];
    vector<Edge> adj[MN];

    void add(int u,int v,int w,int c){
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,w,c,vs});
        adj[v].push_back({u,0,-c,us});
    }

    bool spfa(int S,int T){
        memset(dis,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        queue<int> q;
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
                        vis[e.v]=1;
                        q.push(e.v);
                    }
                }
            }
        }
        memset(cur,0,sizeof(cur));
        return (dis[T]!=INF);
    }

    int dfs(int u,int lim,int T){
        if(u==T) return lim;
        int ret=0;
        vis[u]=1;
        for(int &i=cur[u];i<adj[u].size();i++){
            int v=adj[u][i].v;
            if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].c){
                int p=dfs(v,min(lim,adj[u][i].w),T);
                if(p){
                    adj[u][i].w-=p;
                    adj[v][adj[u][i].id].w+=p;
                    ret+=p;
                    lim-=p;
                    mncst+=p*adj[u][i].c;
                    if(!lim) break;
                }else dis[v]=INF;
            }
        }
        vis[u]=0;
        return ret;
    }

    int dinic(int S,int T){
        int ans=0;
        mncst=0;
        while(spfa(S,T)){
            ans+=dfs(S,INF,T);
        }
        return ans;
    }
}using namespace FYDinic;

int main(){
    cin>>n>>m>>lab;
    for(int i=1;i<=m;i++){
        cin>>x[i]>>y[i]>>d[i];
    }
    for(int i=1;i<=m;i++){
        if(d[i]<=d[lab]&&i!=lab){
            cerr<<x[i]<<' '<<y[i]<<' '<<d[lab]-d[i]+1<<'\n';
            add(x[i],y[i],d[lab]-d[i]+1,1);
            add(y[i],x[i],d[lab]-d[i]+1,1);
        }
    }
    cout<<dinic(x[lab],y[lab]);
    return 0;
}