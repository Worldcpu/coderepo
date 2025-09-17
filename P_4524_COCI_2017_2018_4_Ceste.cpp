#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e4+15,INF=1e18;
struct Edge{
    int v,w1,w2;
};
struct Node{
    int u,w1,w2;

    friend bool operator<(const Node &x,const Node &y){
        return x.w1*x.w2>y.w1*y.w2;
    }
};
int n,m,dis[MN];
vector<Edge> adj[MN];
priority_queue<Node> q;
set<pir> st[MN];

void dijk(int start){
    memset(dis,0x3f,sizeof(dis));
    st[start].insert(pir(0,0));
    q.push({start,0,0});
    while(!q.empty()){
        auto tp=q.top();
        q.pop();
        if(!st[tp.u].count({tp.w1,tp.w2})) continue;
        dis[tp.u]=min(dis[tp.u],tp.w1*tp.w2);
        for(auto e:adj[tp.u]){
            int v1=tp.w1+e.w1,v2=tp.w2+e.w2;
            auto lp=st[e.v].lower_bound({v1,v2});
            if(lp!=st[e.v].begin()&&(*prev(lp)).second<v2) continue;
            while(lp!=st[e.v].end()&&(*lp).second>v2) lp=st[e.v].erase(lp);
            st[e.v].insert({v1,v2});
            q.push({e.v,v1,v2});
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w1,w2;
        cin>>u>>v>>w1>>w2;
        adj[u].push_back({v,w1,w2});
        adj[v].push_back({u,w1,w2});
    }
    dijk(1);
    for(int i=2;i<=n;i++){
        if(dis[i]<=INF) cout<<dis[i]<<'\n';
        else cout<<-1<<'\n';
    }
    return 0;
}