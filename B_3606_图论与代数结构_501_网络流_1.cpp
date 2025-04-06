#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15,INF=1e9;
struct edge
{
    int v;
    int len;
    int fx;//反向边id
};
int n,m,s,t;
int lst[MN],pre[MN],flow[MN];
bool vis[MN];
vector<edge> adj[MN];
bool bfs(){
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(s);
    vis[s]=1;
    flow[s]=INF;
    while (!q.empty())
    {
        int f=q.front();
        q.pop();
        for(int i=0;i<adj[f].size();i++){
            int v=adj[f][i].v;
            if(!vis[v]&&adj[f][i].len){
                vis[v]=1;
                flow[v]=min(flow[f],adj[f][i].len);
                lst[v]=f;
                pre[v]=i;
                if(v==t) return 1;
                q.push(v);
            }
        }
    }
    return 0;
}
int ek(){
    int maxflow=0;
    while (bfs())
    {
        maxflow+=flow[t];
        for(int i=t;i!=s;i=lst[i]){
            adj[lst[i]][pre[i]].len-=flow[t];
            adj[i][adj[lst[i]][pre[i]].fx].len+=flow[t];
        }
    }
    return maxflow;
    
}
int main(){
    cin>>n>>m>>s>>t;
    while (m--)
    {
        int u,v,c;
        cin>>u>>v>>c;
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,c,vs});
        adj[v].push_back({u,0,us});
    }
    cout<<ek();
    return 0;
}