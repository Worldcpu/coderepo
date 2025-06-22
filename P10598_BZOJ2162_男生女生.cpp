#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int MN=1e4+15,INF=1e15,MOD=19921228 ;
struct Edge{
    int v,w,id;
};
int n,m,ans,S=MN-3,T=MN-2,cur[MN],dep[MN],pw[MN],inv[MN];
bool mp[MN][MN];
vector<Edge> adj[MN];

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
        ans+=dfs(S,INF);
    }
    return ans;
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    init();
    int n,m,K;
    cin>>n>>K>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        mp[u][v]=1;

    }
    S=MN-2,T=MN-1;
    for(int i=1;i<=n;i++){
        add(S,i,101);
        add(i+n,T,100);
        for(int j=1;j<=n;j++){
            if(!mp[i][j]) add(i,j+n,INF);
        }
    }
    int tmp=201*n-dinic(),x=tmp%100,y=tmp/100-x;
    cerr<<tmp;
    cout<<x<<" "<<y<<'\n';
    for(int i=0;i<=x;i++){
        for(int j=0;j<=y;j++){
            int w=getC(x,i)*getC(y,j)%MOD*getC((x-i)*(y-j),K)%MOD;
            if((i+j)&1) ans=(ans-w+MOD)%MOD;
            else ans=(ans+w)%MOD;
        }
    }
    cout<<ans;
    return 0;
}
