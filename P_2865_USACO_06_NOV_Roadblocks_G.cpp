#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15;
struct edge{
    int v,w;
};
vector<edge>adj[MN];
typedef pair<int,int> pir;
int dis1[MN],dis2[MN],n,m;
void dij(){
    memset(dis1,0x3f,sizeof(dis1));
    memset(dis2,0x3f,sizeof(dis2));
    priority_queue<pir,vector<pir>,greater<pir>> q;
    q.push(pir(0,1));
    dis1[1]=0;
    while (!q.empty())
    {
        pir f=q.top();
        q.pop();
        int u=f.second,dis=f.first;
        if(dis>dis2[u]) continue;
        for(auto e:adj[u]){
            int v=e.v;
            int nowlen=e.w+dis;
            if(dis1[v]>nowlen){
                dis2[v]=dis1[v];
                dis1[v]=nowlen;
                q.push(pir(dis1[v],v));
                q.push(pir(dis2[v],v));
            }
            if(dis1[v]<nowlen&&dis2[v]>nowlen){
                dis2[v]=nowlen;
                q.push({dis2[v],v});
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dij();
    cout<<dis2[n];
    return 0;
}