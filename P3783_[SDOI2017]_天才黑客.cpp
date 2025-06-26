#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15,MLOG=20;
struct Edge{
    int v,w;
};
struct EDGE{
    int a,b,c,d;
}e[MN];
int n,m,K,S=0,ans[MN],hlca[MN],ntot,prein[MN],preout[MN],sufin[MN],sufout[MN];
vector<int> out[MN],in[MN];
vector<Edge> adj[MN];
vector<pir> vt;

namespace Trie{
    vector<int> g[MN];
    int fa[MN][30],dep[MN],dfn[MN],dfntot;

    void triedfs(int u,int pre){
        dfn[u]=++dfntot;
        fa[u][0]=pre;
        dep[u]=dep[pre]+1;
        for(int i=1;i<=MLOG;i++){
            fa[u][i]=fa[fa[u][i-1]][i-1];
        }
        for(auto v:g[u]){
            triedfs(v,u);
        }
    }

    int lca(int x,int y){
        if(dep[x]>dep[y]) swap(x,y);
        for(int i=MLOG;i>=0;i--){
            if(dep[fa[y][i]]>=dep[x]) y=fa[y][i];
        }
        if(x==y) return x;
        for(int k=MLOG;k>=0;k--){
            if(fa[x][k]!=fa[y][k]){
                x=fa[x][k],y=fa[y][k];
            }
        }
        return fa[x][0];
    }

}using namespace Trie;

namespace Dijkstra{

    int dis[MN];
    bool vis[MN];

    void dijk(int st){
        memset(dis,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        priority_queue<pir,vector<pir>,greater<pir>> q;
        dis[st]=0;
        q.push(pir(0,st));
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v;
                if(dis[v]>dis[u]+e.w){
                    dis[v]=dis[u]+e.w;
                    q.push(pir(dis[v],v));
                }
            }
        }
    }

}using namespace Dijkstra;

bool cmp(pir x,pir y){
    return dfn[x.first]<dfn[y.first];
}

void clear(){
    S=MN-3;
    ntot=dfntot=0;
    memset(dfn,0,sizeof(dfn));
    memset(dep,0,sizeof(dep));
    memset(fa,0,sizeof(fa));
    for(int i=0;i<MN;i++){
        in[i].clear();
        out[i].clear();
        g[i].clear();
        adj[i].clear(); // 添加邻接表清空
    }
}

void solve(){
    cin>>n>>m>>K;
    clear();
    ntot=m<<1;
    for(int i=1;i<=m;i++){
        cin>>e[i].a>>e[i].b>>e[i].c>>e[i].d;
        out[e[i].a].push_back(i);
        in[e[i].b].push_back(i);
    }
    for(int i=1;i<K;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back(v);
    }
    triedfs(1,0);
    for(int i=1;i<=m;i++){
        adj[i].push_back({i+m,e[i].c});
        if(e[i].a==1) adj[S].push_back({i,0});
    }
    for(int i=1;i<=n;i++){
        vt.clear();
        for(auto p:in[i]) vt.push_back(pir(e[p].d,p+m));
        for(auto p:out[i]) vt.push_back(pir(e[p].d,p));
        sort(vt.begin(),vt.end(),cmp);
        for(int j=0;j<vt.size();j++){
            prein[j]=++ntot;
            preout[j]=++ntot;
            sufin[j]=++ntot;
            sufout[j]=++ntot;
        }
        for(int j=0;j+1<vt.size();j++){
            hlca[j]=lca(vt[j].first,vt[j+1].first);
            adj[prein[j+1]].push_back({prein[j],0});
            adj[preout[j]].push_back({preout[j+1],0});
            adj[sufin[j]].push_back({sufin[j+1],0});
            adj[sufout[j+1]].push_back({sufout[j],0});
        }
        for(int j=0;j<vt.size();j++){
            if(vt[j].second<=m){
                adj[sufin[j]].push_back({vt[j].second,0});
                adj[prein[j]].push_back({vt[j].second,0});
            }
            else{
                adj[vt[j].second].push_back({sufout[j],0});
                adj[vt[j].second].push_back({preout[j],0});
            }
        }
        for(int j=0;j+1<vt.size();j++){
            // 修正边权：使用LCA的深度
            adj[sufout[j+1]].push_back({prein[j], dep[hlca[j]]-1});
            adj[preout[j]].push_back({sufin[j+1], dep[hlca[j]]-1});
        }
    }
    dijk(S);
    memset(ans,0x3f,sizeof(ans));
    for(int i=1;i<=m;i++){
        ans[e[i].b]=min(ans[e[i].b],dis[i+m]);
    }
    for(int i=2;i<=n;i++) cout<<ans[i]<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
