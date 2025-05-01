#include<bits/stdc++.h>
using namespace std;
constexpr int MN=150,AWA=1e6+15;
constexpr int INF=0x3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
int n,K,S,T,a,b,c,cnt,mincst,cur[AWA],dis[AWA],pos[MN][MN];
bool vis[AWA];
vector<Edge> adj[AWA];

int gpos(int x,int y,int k){
    return pos[x][y]+k*n*n;
}

void add(int u,int v,int w,int c){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,c,vs});
    adj[v].push_back({u,0,-c,us});
}

bool spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
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
        cur[u]=i;
        int v=adj[u][i].v;
        if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].c){
            int p=dfs(v,min(lim,adj[u][i].w));
            if(p){
                adj[u][i].w-=p;
                adj[v][adj[u][i].id].w+=p;
                ret+=p;
                lim-=p;
                mincst+=p*adj[u][i].c;
                if(!lim) break;
            }else dis[v]=INF;
        }
    }
    vis[u]=0;
    return ret;
}

int dinic(){
    int mxflow=0;
    while(spfa()){
        mxflow+=dfs(S,INF);
    }
    return mxflow;
}

int main(){
    cin>>n>>K>>a>>b>>c;
    S=(n*n*(K+1)+1);
    T=S+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            pos[i][j]=++cnt;
        }
    }
    add(S,pos[1][1],1,0);
    for(int i=1;i<=K;i++){
        add(gpos(n,n,i),T,1,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            if(x){
                for(int k=1;k<=K;k++){
                    add(gpos(i,j,k),gpos(i,j,0),1,a);
                }
                if(i>1){
                    add(gpos(i,j,0),gpos(i-1,j,1),1,b);
                }
                if(j>1){
                    add(gpos(i,j,0),gpos(i,j-1,1),1,b);
                }
                if(i<n){
                    add(gpos(i,j,0),gpos(i+1,j,1),1,0);
                }
                if(j<n){
                    add(gpos(i,j,0),gpos(i,j+1,1),1,0);
                }
            }else{
                for(int k=0;k<K;k++){
                    if(i>1){
                        add(gpos(i,j,k),gpos(i-1,j,k+1),1,b);
                    }
                    if(j>1){
                        add(gpos(i,j,k),gpos(i,j-1,k+1),1,b);
                    }
                    if(i<n){
                        add(gpos(i,j,k),gpos(i+1,j,k+1),1,0);
                    }
                    if(j<n){
                        add(gpos(i,j,k),gpos(i,j+1,k+1),1,0);
                    }
                }
                add(gpos(i,j,K),gpos(i,j,0),1,a+c);
            }
        }
    }
    dinic();
    cout<<mincst;
    return 0;
}