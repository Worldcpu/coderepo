#include<bits/stdc++.h>
#define double long double
using namespace std;
constexpr int MN=55;
constexpr double eps=1e-10;
struct Edge{
    int v;
    double w;
};
int n,m,tot;
double l,r,dis[MN];
bool vis[MN];
vector<Edge> adj[MN];

int cmp(double x,double y){
    if(fabs(x-y)<eps) return 0;
    if(x>y) return 1;
    return -1;
}

bool dfs(int u,double k){
    vis[u]=1;
    for(auto e:adj[u]){
        int v=e.v;
        auto w=e.w;
        if(dis[v]>dis[u]+w-k){
            dis[v]=dis[u]+w-k;
            if(vis[v]||dfs(v,k)){
                return vis[u]=0,1;
            }
        }
    }
    return vis[u]=0;
}

bool check(double k){
    memset(dis,0,sizeof(dis));
    for(int i=1;i<=n;i++){
        if(dfs(i,k)) return 1;
    }
    return 0;
}

void init(){
    for(int i=1;i<=n;i++) adj[i].clear(),vis[i]=0;
}

void solve(){
    init();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    l=0,r=1e9;
    while(r-l>eps){
        double mid=(l+r)/2;
        if(check(mid)) r=mid;
        else l=mid;
    }
    if(cmp(l,1e9)==0) cout<<"No cycle found.\n";
    else cout<<fixed<<setprecision(2)<<(l+r)/2<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cout<<"Case #"<<++tot<<": ";
        solve();
    }
    return 0;
}
