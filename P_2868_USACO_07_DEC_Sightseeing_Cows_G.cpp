#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=2000;
constexpr double eps=1e-8;
struct Edge{
    int v;
    int w;
};
struct Node{
    int u;
    double w;
};
int n,m,cnt[MN];
double dis[MN];
ll f[MN],t[MN];
bool vis[MN];
vector<Edge> adj[MN];

bool spfa(double k){
    queue<int> q;
    for(int i=1;i<=n;i++){
        dis[i]=0;
        cnt[i]=vis[i]=1;
        q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(auto e:adj[u]){
            if(dis[e.v]>dis[u]+e.w*k-f[u]){
                dis[e.v]=dis[u]+e.w*k-f[u];
                if(!vis[e.v]){
                    vis[e.v]=1;
                    q.push(e.v);
                    cnt[e.v]++;
                    if(cnt[e.v]>=n) return 1;
                }
            }
        }
    }
    return 0;
}

bool check(double k){
    return spfa(k);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>f[i];
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    double l=0,r=1e18;
    while(l+eps<r){
        double mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    cout<<fixed<<setprecision(2)<<r;
    return 0;
}