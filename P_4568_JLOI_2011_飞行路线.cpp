#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
const int MN=5e4+15,MK=15;
int n,m,k,s,t;
struct edge
{
    int v,w;
};

struct node
{
    int u,dist;
    bool operator<(const node&x)const{
        return dist>x.dist;
    }
};
bool vis[MK*MN];
int dis[MK*MN];
vector<edge> adj[MN*MK];
inline void add(int u,int v,int w){
    adj[u].push_back({v,w});
}
void dijk(int s){
    priority_queue<node> q;
    q.push({s,0});
    dis[s]=0;
    while (!q.empty())
    {
        node f=q.top();
        q.pop();
        int u=f.u,d=f.dist;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=0;i<adj[u].size();i++){
            int v=adj[u][i].v,w=adj[u][i].w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push({v,dis[v]});
            }
        }
    }
    
}
int main(){
    memset(dis,0x3f,sizeof(dis));
    cin>>n>>m>>k>>s>>t;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w);
        add(v,u,w);
        for(int j=1;j<=k;j++){
            add(u+(j-1)*n,v+j*n,0);
            add(v+(j-1)*n,u+j*n,0);
            //j-1向j层建边
            add(u+j*n,v+j*n,w);
            add(v+j*n,u+j*n,w);
            //j层的建边
        }
    }
    //防止还没有走到最后一层就停了
    for(int i=1;i<=k;i++){
        add(t+(i-1)*n,t+i*n,0);
    }
    dijk(s);
    cout<<dis[t+k*n];
    return 0;
}