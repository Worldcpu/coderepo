#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
const int MN=1e4+15,MK=3;
int n,m,dis[MN*MK];
struct edge
{
    int v,w;
};

vector<edge> adj[MN*MK];
void dij(){
    priority_queue<pir,vector<pir>,greater<pir>> q;
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    q.push(pir(0,1));
    while (!q.empty())
    {
        pir f=q.top();
        q.pop();
        int u=f.second,disu=f.first;
        if(disu>dis[u]) continue;
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(dis[v]>disu+w){
                dis[v]=disu+w;
                q.push(pir(dis[v],v));
            }
        }
    }
    
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w,d;
        cin>>u>>v>>w>>d;
        if(!d){
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
            for(int j=1;j<=2;j++){
                adj[u+j*n].push_back({v+j*n,w});
                adj[v+j*n].push_back({u+j*n,w});               
            }
        }else{
            for(int j=1;j<=2;j++){
                adj[u+(j-1)*n].push_back({v+j*n,w});
                adj[v+(j-1)*n].push_back({u+j*n,w});
            }
        }
    }
    for(int i=1;i<=2;i++){
        adj[n+(i-1)*n].push_back({n+i*n,0});
    }
    dij();
    cout<<dis[n]-dis[3*n];
    return 0;
}