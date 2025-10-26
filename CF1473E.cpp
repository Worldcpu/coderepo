#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,w;
};
struct Node{
    int dis,u,stmx,stmn;

    friend bool operator>(const Node &x,const Node &y){
        if(x.dis==y.dis){
            if(x.u==y.u){
                if(x.stmx==y.stmx) return x.stmn>y.stmn;
                return x.stmx>y.stmx;
            }
            return x.u>y.u;
        }
        return x.dis>y.dis;
    }

};
int n,m,f[MN][2][2];
vector<Edge> adj[MN];
map<tuple<int,int,int>,bool> vis;

void dijkstra(){
    priority_queue<Node,vector<Node>,greater<Node>> q;
    memset(f,0x3f,sizeof(f));
    f[1][0][0]=0;
    q.push({0,1,0,0});
    while(!q.empty()){
        auto tp=q.top();
        q.pop();
        if(vis[{tp.u,tp.stmx,tp.stmn}]) continue;
        vis[{tp.u,tp.stmx,tp.stmn}]=1;
        for(auto e:adj[tp.u]){
            if(f[e.v][tp.stmx][tp.stmn]>f[tp.u][tp.stmx][tp.stmn]+e.w){
                f[e.v][tp.stmx][tp.stmn]=f[tp.u][tp.stmx][tp.stmn]+e.w;
                q.push({f[e.v][tp.stmx][tp.stmn],e.v,tp.stmx,tp.stmn});
            }
            if(tp.stmx==0&&f[e.v][1][tp.stmn]>f[tp.u][tp.stmx][tp.stmn]){
                f[e.v][1][tp.stmn]=f[tp.u][tp.stmx][tp.stmn];
                q.push({f[e.v][1][tp.stmn],e.v,1,tp.stmn});
            }
            if(tp.stmn==0&&f[e.v][tp.stmx][1]>f[tp.u][tp.stmx][tp.stmn]+e.w*2){
                f[e.v][tp.stmx][1]=f[tp.u][tp.stmx][tp.stmn]+e.w*2;
                q.push({f[e.v][tp.stmx][1],e.v,tp.stmx,1});
            }
        }
    }

}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dijkstra();
    for(int i=2;i<=n;i++){
        cout<<min(f[i][0][0],f[i][1][1])<<' ';
    }
    return 0;
}