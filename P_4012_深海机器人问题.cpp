#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MK=520,INF=0x3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
int p,q,a,b,tot,e[MK][MK],mp[MK][MK],cur[MN],dis[MN],S=MN-3,T=MN-2,mincst;
bool vis[MN];
vector<Edge> adj[MN];

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

int main(){
    cin>>a>>b>>p>>q;
    for(int i=0;i<=p;i++){
        for(int j=0;j<=q;j++){
            mp[i][j]=++tot;
        }
    }
    for(int i=0;i<=p;i++){
        for(int j=0;j<q;j++){
            cin>>e[i][j];
            add(mp[i][j],mp[i][j+1],1,-e[i][j]);
            add(mp[i][j],mp[i][j+1],INF,0);
        }
    }
    for(int i=0;i<=q;i++){
        for(int j=0;j<p;j++){
            cin>>e[i][j];
            add(mp[j][i],mp[j+1][i],1,-e[i][j]);
            add(mp[j][i],mp[j+1][i],INF,0);
        }
    }
    for(int i=1;i<=a;i++){
        int x,y,w;
        cin>>w>>x>>y;
        add(S,mp[x][y],w,0);
    }
    for(int i=1;i<=a;i++){
        int x,y,w;
        cin>>w>>x>>y;
        add(mp[x][y],T,w,0);
    }
    dinic();
    cout<<-mincst;
    return 0;
}