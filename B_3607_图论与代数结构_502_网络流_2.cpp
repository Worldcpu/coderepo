//dinic
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=1e5+15,INF=1e15;
struct edge
{
    int v;
    ll len;
    int id;
};
vector<edge> adj[MN];
int n,m,s,t;
ll flow[MN],cur[MN],dep[MN];
bool bfs(){
    memset(dep,-1,sizeof(dep));
    queue<int> q;
    q.push(s);
    dep[s]=0;
    while (!q.empty())
    {
        int f=q.front();
        q.pop();
        for(auto e:adj[f]){
            int v=e.v,len=e.len;
            if(dep[v]==-1&&len){
                dep[v]=dep[f]+1;
                q.push(v);
            }
        }
    }
    return (dep[t]!=-1);
}
ll dfs(int u,ll limit){
    if(u==t) return limit;
    ll flow=0;
    for(ll &i=cur[u];i<adj[u].size();i++){
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&(adj[u][i].len)){
            int p=dfs(v,min(adj[u][i].len,limit));
            if(p){
                adj[u][i].len-=p;
                adj[v][adj[u][i].id].len+=p;
                return p;
            }else dep[v]=-1;
        }
    }
    return 0;
}
ll dinic(){
    ll ans=0,flow;
    while (bfs()){
        memset(cur,0,sizeof(cur));
        while (flow=dfs(s,INF)){
            ans+=flow;
        }
    }
    return ans;
}
int main(){
    cin>>n>>m>>s>>t;
    while (m--)
    {
        int u,v,len;
        cin>>u>>v>>len;
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,len,vs});
        adj[v].push_back({u,0,us});
    }
    cout<<dinic();
    return 0;
}