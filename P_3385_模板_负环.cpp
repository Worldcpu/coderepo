#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int MN=2e3+15;
struct edge
{
    int v,w;
};
int dis[MN],cnt[MN]{},T,n,m;
bool vis[MN];
vector<edge> adj[MN];
bool spfa(int s){
    queue<int> q;
    cnt[s]++;
    dis[s]=0;
    q.push(s);
    while (!q.empty())
    {
        int f=q.front();
        q.pop();
        vis[f]=0;
        for(int i=0;i<adj[f].size();i++){
            int v=adj[f][i].v,w=adj[f][i].w;
            if(dis[v]>dis[f]+w){
                dis[v]=dis[f]+w;
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                    cnt[v]++;
                    if(cnt[v]>n) return 1;
                }
            }
        }
    }
    return 0;
}
int main(){
    cin>>T;
    while (T--)
    {
        memset(dis,0x3f,sizeof(dis));
        memset(cnt,0,sizeof(cnt));
        memset(vis,0,sizeof(vis));
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            adj[i].clear();
        }
        for(int i=1;i<=m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            if(w>=0){
                adj[u].push_back({v,w});
                adj[v].push_back({u,w});
            }else{
                adj[u].push_back({v,w});
            }
        }
        if(spfa(1)){
            cout<<"YES\n";
        }else cout<<"NO\n";
    }
    
    return 0;
}