#include<bits/stdc++.h>
#define INF 1e9
#define pir pair<double,int>
using namespace std;
const int MN=520;
int n,m,pre[MN],nx[MN],ny[MN];
struct edge
{
    int v;
    double w;
};
vector<edge> adj[MN];
bool vis[MN];
double dis[MN];
double clac(int a,int b){
    return sqrt((nx[a]-nx[b])*(nx[a]-nx[b])+(ny[a]-ny[b])*(ny[a]-ny[b]));
}
void dij(int fu,int fv){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        vis[i]=0;
    }
    dis[1]=0;
    priority_queue<pir,vector<pir>,greater<pir>> q;
    q.push(pir(0,1));
    while (!q.empty())
    {
        pir f=q.top();
        q.pop();
        int u=f.second;
        double fw=f.first;
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
            int v=e.v;
            double w=e.w;
            if((u==fu&&v==fv)||(u==fv&&v==fu)) continue;
            if(dis[v]>fw+w){
                dis[v]=fw+w;
                if(fu==-1&&fv==-1){
                    pre[v]=u;
                }
                if(!vis[v]) q.push(pir(dis[v],v));
            }
        }
    }
    
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nx[i]>>ny[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        double w=clac(u,v);
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    double ans=INF;
    dij(-1,-1);
    for(int i=n;i!=1;i=pre[i]){
        dij(pre[i],i);
        ans=min(ans,dis[n]);
    }
    if(ans>=INF) cout<<-1;
    else cout<<fixed<<setprecision(2)<<ans;
    return 0;
}