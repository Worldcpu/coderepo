#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15,MK=520,INF=0x3f3f3f3f;
struct Edge{
    int v,w,id;
};
struct Node{
    int x,y,w;
}a[MN];
int fx[4]={1,-1,0,0},fy[4]={0,0,1,-1};
int S=MN-3,T=MN-2,C,R,n,tot,cur[MN],dep[MN];
vector<Edge> adj[MN];
map<pir,int> mp;

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

int getcol(int x,int y){
    if(y%2==1) return x%4+1;
    if(x%2==1) return x%4;
    return x%4+2;
}

int main(){
    cin>>R>>C>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y>>a[i].w;
        mp[pir(a[i].x,a[i].y)]=i;
    }
    for(int i=1;i<=n;i++){
        int cur=getcol(a[i].x,a[i].y);
        add(i,i+n,a[i].w);
        if(cur==1){
            add(S,i,INF);
        }
        if(cur==4){
            add(i+n,T,INF);
            continue;
        }
        for(int j=0;j<4;j++){
            int nx=a[i].x+fx[j],ny=a[i].y+fy[j];
            if(nx<1||nx>R||ny<1||ny>C||!mp[pir(nx,ny)]) continue;
            int nxt=getcol(nx,ny);
            if(nxt==cur+1){
                add(i+n,mp[pir(nx,ny)],INF);
            }
        }
    }
    cout<<dinic();
    return 0;
}
