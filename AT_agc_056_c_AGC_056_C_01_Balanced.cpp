#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
struct Edge{
    int v,w;
};
int n,m,L[MN],R[MN],dis[MN];
vector<Edge> adj[MN];


int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        adj[l-1].push_back({r,0});
        adj[r].push_back({l-1,0});
    }
    for(int i=1;i<=n;i++){
        adj[i].push_back({i-1,1});
        adj[i-1].push_back({i,1});
    }
    deque<pir> q;
    memset(dis,0x3f,sizeof(dis));
    q.push_back(pir(0,0));
    dis[0]=0;
    while(!q.empty()){
        auto p=q.front();
        int u=p.first,disu=p.second;
        q.pop_front();
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(dis[v]>dis[u]+e.w){
                dis[v]=dis[u]+e.w;
                if(e.w){
                    dis[v]=p.second+1;
                    q.push_back(pir(v,dis[v]));
                }else{
                    dis[v]=p.second;
                    q.push_front(pir(v,dis[v]));
                }
            }
        }
    }   
    for(int i=1;i<=n;i++){
        cout<<(dis[i]-dis[i-1]<0);
    }
    return 0;
}