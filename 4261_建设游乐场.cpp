#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f3f3f3f3f,MT=520;
int a[MT][MT],w[MT][MT],id[MT][MT][3],dtot,n,m,sumw,fs,ft;

namespace FYDinic{
    struct Edge{
        int v,w,c,id;
    };
    int S=MN-3,T=MN-2,mncst,dis[MN],cur[MN];
    bool vis[MN];
    vector<Edge> adj[MN];

    void add(int u,int v,int w,int c){
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,w,c,vs});
        adj[v].push_back({u,0,-c,us});
    }

    bool spfa(int S,int T){
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
        return (dis[T]>-INF);
    }

    int dfs(int u,int lim,int T){
        if(u==T) return lim;
        vis[u]=1;
        int ret=0;
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
        int ans=0,flow;
        mncst=0;
        while(spfa(S,T)){
            while(flow=dfs(S,INF,T)) ans+=flow;
        }
        return ans;
    }
}using namespace FYDinic;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>w[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<3;k++){
                id[i][j][k]=++dtot;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]) continue;
            sumw+=w[i][j];
            if((i+j)&1){
                fs+=2;
                add(S,id[i][j][2],2,0);
                add(id[i][j][2],id[i][j][0],1,w[i][j]);
                add(id[i][j][2],id[i][j][0],1,0);
                add(id[i][j][2],id[i][j][1],1,w[i][j]);
                add(id[i][j][2],id[i][j][1],1,0);
                if(id[i-1][j][0])add(id[i][j][0],id[i-1][j][0],1,0);
                if(id[i+1][j][0])add(id[i][j][0],id[i+1][j][0],1,0);
                if(id[i][j-1][0])add(id[i][j][1],id[i][j-1][1],1,0);
                if(id[i][j+1][0])add(id[i][j][1],id[i][j+1][1],1,0);
            }else{
                ft+=2;
                add(id[i][j][2],T,2,0);
                add(id[i][j][0],id[i][j][2],1,0);
                add(id[i][j][0],id[i][j][2],1,w[i][j]);
                add(id[i][j][1],id[i][j][2],1,0);
                add(id[i][j][1],id[i][j][2],1,w[i][j]);
            }
        }
    }
    if(fs!=ft){
        cout<<-1;
        return 0;
    }
    cerr<<"QWQWQWQWQ\n";
    if(dinic(S,T)!=fs){
        cout<<-1;
        return 0;
    }else cout<<mncst-sumw;
    return 0;
}