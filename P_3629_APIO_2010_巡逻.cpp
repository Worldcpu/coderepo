#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
struct Edge
{
    int v,w;
};
struct Node{
    int u,fa,len;
};
vector<Edge> adj[MN];
int n,k,fa[MN],d[MN];
bool vis[MN],visd[MN];

pair<int,int> bfs(int start){
    int maxx=-1e9,ans=1;
    queue<Node> q;
    q.push({start,0,0});
    while(!q.empty()){
        Node f=q.front();
        q.pop();
        fa[f.u]=f.fa;
        if(f.len>maxx){
            maxx=f.len;
            ans=f.u;
        }
        for(auto e:adj[f.u]){
            if(e.v==f.fa) continue;
            q.push({e.v,f.u,f.len+1});
        }
    }
    return pair<int,int>(ans,maxx);
}

int ans=0;

void dp(int u,int pre){
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==pre) continue;
        dp(v,u);
        if(vis[u]&&vis[v]) w=-1;
        ans=max(ans,d[u]+d[v]+w);
        d[u]=max(d[u],d[v]+w);
    }
}

int main(){
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,1});
        adj[v].push_back({u,1});
    }
    pir bfs1=bfs(1);
    pir bfs2=bfs(bfs1.first);
    if(k==1){
        cout<<(2*n-1)-bfs2.second;
        return 0;
    }
    for(int i=bfs2.first;i;i=fa[i]){
        vis[i]=1;
    }
    //cout<<bfs2.first<<'\n';
    //for(int i=1;i<=n;i++) cout<<vis[i]<<" ";
    dp(1,0);
    cout<<n*2-bfs2.second-ans;
    return 0;
}