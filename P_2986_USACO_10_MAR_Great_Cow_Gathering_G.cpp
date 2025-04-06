#include<iostream>
#include<vector>
#define ll unsigned long long
using namespace std;
const int MN=1e5+15;
struct edge
{
    int v,w;
};

ll n,siz[MN],dis[MN],c[MN],ans[MN],minn=1e16;
vector<edge> adj[MN];

void dfs1(int u,int fa){
    siz[u]=c[u];
    for(auto v:adj[u]){
        if(v.v!=fa){
            dfs1(v.v,u);
            siz[u]+=siz[v.v];
            dis[u]+=dis[v.v]+siz[v.v]*v.w;
        }
    }
}
void dfs2(int u,int fa){
    for(auto v:adj[u]){
        if(v.v!=fa){
            ans[v.v]=ans[u]+(siz[1]-2*siz[v.v])*v.w;
            dfs2(v.v,u);
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs1(1,0);
    ans[1]=dis[1];
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        minn=min(minn,ans[i]);
    }
    //cout<<endl;
    cout<<minn;
    return 0;
}