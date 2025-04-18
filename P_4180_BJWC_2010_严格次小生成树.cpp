#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,ME=3e5+15,ML=20,INF=1e9;
struct Edge{
    int u,v,w;
    bool selc;
}e[ME];
struct VCTEdge{
    int v,w;
};
int n,m,pre[MN],fa[MN][30],g[MN][30][2],dep[MN],sum;
vector<VCTEdge> adj[MN];

int root(int x){
    if(pre[x]==x) return x;
    else return pre[x]=root(pre[x]);
}

bool cmp(Edge x,Edge y){
    return x.w<y.w;
}

void kru(){
    for(int i=1;i<=n;i++) pre[i]=i;
    sort(e+1,e+1+m,cmp);
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru==rv) continue;
        pre[rv]=ru;
        adj[e[i].u].push_back({e[i].v,e[i].w});
        adj[e[i].v].push_back({e[i].u,e[i].w});
        e[i].selc=1;
        sum+=e[i].w;
    }
}

void dfs(int u,int pree,int w){
    fa[u][0]=pree;
    dep[u]=dep[pree]+1;
    g[u][0][1]=-INF;
    g[u][0][0]=w;
    for(int i=1;i<=ML;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
        g[u][i][0]=max(g[u][i-1][0],g[fa[u][i-1]][i-1][0]);
        if(g[u][i-1][0]==g[fa[u][i-1]][i-1][0]){
            g[u][i][1]=max(g[u][i-1][1],g[fa[u][i-1]][i-1][1]);
        }else if(g[u][i-1][0]<g[fa[u][i-1]][i-1][0]){
            g[u][i][1]=max(g[u][i-1][0],g[fa[u][i-1]][i-1][1]);
        }else g[u][i][1]=max(g[u][i-1][1],g[fa[u][i-1]][i-1][0]);
    }
    for(auto e:adj[u]){
        if(e.v==pree) continue;
        dfs(e.v,u,e.w);
    }
}

int lca(int x,int y){
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    for(int i=20;i>=0;i--){
        if(dep[fa[y][i]]>=dep[x]) y=fa[y][i];
    }
    if(x==y) return x;
    for(int k=20;k>=0;k--){
        if(fa[x][k]!=fa[y][k]){
            x=fa[x][k],y=fa[y][k];
        }
    }
    return fa[x][0];
}

int getg(int u,int v,int w){
    int ans=-INF;
    for(int i=20;i>=0;i--){
        if(dep[fa[u][i]]>=dep[v]){
            if(w==g[u][i][0]) ans=max(ans,g[u][i][1]);
            else ans=max(ans,g[u][i][0]);
            u=fa[u][i];
        }
    }
    return ans;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
        e[i].selc=0;
    }
    kru();
    dfs(1,0,0);
    int ret=INF;
    for(int i=1;i<=m;i++){
        if(e[i].selc) continue;
        int lcuv=lca(e[i].u,e[i].v);
        ret=min(ret,sum-max(getg(e[i].u,lcuv,e[i].w),getg(e[i].v,lcuv,e[i].w))+e[i].w);
    }
    cout<<ret;
    return 0;
}