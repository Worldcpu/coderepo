#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
struct Edge{
    int u,v;
}e[MN];
struct EEdge{
    int v,w;
};
int n,m;
bool f[MN];
vector<int> G[MN];
vector<EEdge> adj[MN];

namespace SPFA{
    int dis[MN],vis[MN],cnt[MN];

    void spfa(int st){
        memset(dis,0x3f,sizeof(dis));
        queue<int> q;
        q.push(st);
        dis[st]=0;
        vis[st]=1;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+e.w){
                    dis[v]=dis[u]+e.w;
                    cnt[v]=cnt[u]+1;
                    if(cnt[v]>n){
                        cout<<-1;
                        exit(0);
                    }
                    if(!vis[v]){
                        vis[v]=1;
                        q.push(v);
                    }
                }
                
            }
        }
    }
}using namespace SPFA;

namespace DFNTree{
    bool vis[MN];

    void dfs(int u){
        vis[u]=1;
        for(auto v:G[u]){
            if(vis[v]) continue;
            dfs(v);
            f[u]|=f[v];
        }
    }
}

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

signed main(){
    srand(time(0));
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v;
        G[e[i].u].push_back(e[i].v);
    }
    f[n]=1;
    DFNTree::dfs(1);
    if(!f[1]){
        cout<<-1;
        cerr<<"QWQ\n";
        return 0;
    }
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v;
        if(!f[u]||!f[v]) continue;
        adj[u].push_back({v,9});
        adj[v].push_back({u,-1});
    }
    spfa(1);
    cout<<n<<' '<<m<<'\n';
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v,w=dis[e[i].v]-dis[e[i].u];
        if(w>0&&w<10){
        }else w=1;
        cout<<u<<' '<<v<<' '<<w<<'\n';

    }
    
    
    return 0;
}