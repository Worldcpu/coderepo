#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
const int MN=5e3+15;
int n,m,dis[MN],cnt[MN];
bool vis[MN];
struct edge
{
    int v,w;
};
vector<edge> adj[MN];
bool spfa(int s){
    queue<int> q;
    q.push(s);
    dis[s]=0;
    vis[s]=1;
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
                    cnt[v]++;
                    if(cnt[v]==n+1){
                        return 0;
                    }
                    q.push(v);
                }
            }
        }
    }
    return 1;
}
int main(){
    memset(dis,0x3f,sizeof(dis));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        adj[0].push_back({i,0});
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[v].push_back({u,w});
    }
    if(!spfa(0)){
        cout<<"NO";
    }else{
        for(int i=1;i<=n;i++){
            cout<<dis[i]<<" ";
        }
    }
    return 0;
}