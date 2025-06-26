#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,ME=2500,INF=0x3f3f3f3f,MOD=19921228;
struct Edge{
    int v,w,id;
};
int sum,n,m,K,S=MN-3,T=MN-2,cur[MN],dep[MN],C[ME][ME];
vector<Edge> adj[MN];
bool mp[ME][ME];

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

void init(){
    C[0][0]=1;
    for(int i=1;i<ME;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
        }
    }
}

signed main(){
    init();
    cin>>n>>K>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        mp[u][v]=1;
    }
    for(int i=1;i<=n;i++){
        add(S,i,101);
        add(i+n,T,100);
        for(int j=1;j<=n;j++){
            if(!mp[i][j]) add(i,j+n,INF);
        }
    }
    int ret=dinic(),x=ret%100,y=ret/100-x;
    x=n-x,y=n-y;
    cout<<x<<" "<<y<<'\n';
    int ans=0;
    for(int i=0;i<=x;i++){
        for(int j=0;j<=y;j++){
            ret=(C[x][i]*C[y][j])%MOD;
            ret=(ret*C[(x-i)*(y-j)][K])%MOD;
            if((i^j)&1) ans=(ans-ret+MOD)%MOD;
            else ans=(ans+ret)%MOD;
        }
    }
    cout<<ans;
    return 0;
}
