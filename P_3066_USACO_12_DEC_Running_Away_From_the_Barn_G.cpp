#include<iostream>
#include<algorithm>
#include<vector>
#define int long long
using namespace std;
const int MN=2e5+15,ML=20;
struct edge
{
    int v,w;
};
int n,m,ans[MN];
vector<edge> adj[MN];
int fa[MN][30],dep[MN],dis[MN],cf[MN];
void dfs(int u,int pre){
    dep[u]=dep[pre]+1;
    fa[u][0]=pre;
    for(int i=1;i<=ML;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(auto v:adj[u]){
        if(v.v!=pre){
            dis[v.v]=dis[u]+v.w;
            dfs(v.v,u);
        }
    }
}
int getfar(int u){
    int k=u;
    for(int i=20;i>=0;i--){
        if(dis[u]-dis[fa[k][i]]<=m){
            k=fa[k][i];
        }
    }
    return k;
}

void getans(int u,int fa){
    for(auto e:adj[u]){
        if(e.v!=fa){
            getans(e.v,u);
            ans[u]+=ans[e.v];
        }
    }
    ans[u]+=cf[u];
}

signed main(){
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        int v,w;
        cin>>v>>w;
        adj[i].push_back({v,w});
        adj[v].push_back({i,w});
    }
    
    dfs(1,0);
    dis[0]=-1e9;
    for(int i=1;i<=n;i++){
        int d=getfar(i);
        cf[i]++;
        cf[fa[d][0]]--;
    }
    getans(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}