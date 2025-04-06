#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
const int MN=5e3+15;
struct edge
{
    int v,w;
};
vector<edge> adj[MN];
int n,m,a,b,c,cnt[MN],dis[MN];
bool vis[MN];
bool spfa(int s){
    queue<int> q;
    dis[s]=0;
    cnt[s]++;
    q.push(s);
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
                    if(cnt[v]==n+1) return 0;
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
        int op;
        cin>>op>>a>>b;
        if(op==1){
            cin>>c;
            adj[a].push_back({b,-c});
        }else if(op==2){
            cin>>c;
            adj[b].push_back({a,c});
        }else{
            adj[a].push_back({b,0});
            adj[b].push_back({a,0});
        }
    }
    if(spfa(0)){
        cout<<"Yes";
    }else cout<<"No";
    return 0;   
}