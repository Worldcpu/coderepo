#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int u,v;
}e[MN];
int n,K,ret[MN];
bool vis[MN];
vector<int> adj[MN];
priority_queue<pir,vector<pir>,greater<pir>> q;

void bfs(){
    while(!q.empty()){
        int u=q.top().second,dis=q.top().first;
        q.pop();
        vis[u]=1;
        for(auto v:adj[u]){
            if(!vis[v]){
                vis[v]=1;
                ret[v]=dis+1;
                q.push(pir(ret[v],v));
            }
        }
    }
}

bool check(int x,int y){
    return abs(ret[x]-ret[y])==1;
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        e[i]={u,v};
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin>>K;
    for(int i=1;i<=K;i++){
        int x,y;
        cin>>x>>y;
        ret[x]=y;
        vis[x]=1;
        q.push(pir(y,x));
    }
    bfs();
    for(int i=1;i<n;i++){
        if(!check(e[i].u,e[i].v)){
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        cout<<ret[i]<<'\n';
    }
    return 0;
}