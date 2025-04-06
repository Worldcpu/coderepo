#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#define pir pair<int,int>
using namespace std;
const int MN=1e5+15;
int n,m,s,t,x,h[MN],g[MN],cnt[MN];
const int INF=0x3f3f3f3f;
struct edge
{
    int v,w;
};
struct node{
    int v,nh,ng;
    bool operator<(const node&x)const{
        return nh+ng<x.nh+x.ng;
    }
};
vector<edge> adj[MN],adjh[MN];
void dij(){
    priority_queue<pir,vector<pir>,greater<pir>>q;
    q.push(pir(0,t));
    h[t]=0;
    while(!q.empty()){
        pir f=q.top();
        q.pop();
        int u=f.second,w=f.first;
        if(w>h[u]) continue;
        for(int i=0;i<adjh[u].size();i++){
            edge e=adjh[u][i];
            int v=e.v,ew=e.w;
            if(h[v]>h[u]+ew){
                h[v]=h[u]+ew;
                q.push(pir(h[v],v));
            }
        }
    }
}
bool astar(){
    if(h[s]==INF) return 0;
    priority_queue<node> q;
    q.push({s,0,0});
    while(!q.empty()){
        node f=q.top();
        q.pop();
        int u=f.v,fh=f.nh,fg=f.ng;
        cnt[u]++;
        if(u==t&&cnt[u]==x){
            cout<<fg;
            return 1;
        }
        if(cnt[u]>x) continue;
        for(int i=0;i<adj[u].size();i++){
            edge e=adj[u][i];
            int v=e.v,ew=e.w;
            q.push({v,h[v],fg+ew});
        }
    }
    return 0;
}
int main(){
    memset(h,0x3f,sizeof(h));
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adjh[v].push_back({u,w});
    }
    cin>>s>>t>>x;
    dij();
    if(!astar()){
        cout<<-1;
    }
    return 0;
}