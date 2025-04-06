#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#define endl '\n'
using namespace std;
const int MN=2e6+16,MOD=100003;
struct edge
{
    int v,w;
};
struct node
{
    int u,d;
    bool operator<(const node&x)const{
        return d>x.d;
    }
};

vector<edge> adj[MN];
int n,m,dis[MN],zdl[MN];
void dijk(){
    priority_queue<node> q;
    q.push((node){1,0});
    dis[1]=0;
    zdl[1]=1;
    while (!q.empty())
    {
        node f=q.top();
        q.pop();
        int u=f.u,len=f.d;
        for(int i=0;i<adj[u].size();i++){
            int v=adj[u][i].v,w=adj[u][i].w;
            if(len+w==dis[v]){
                zdl[v]=(zdl[v]+zdl[u])%MOD;
            }
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                zdl[v]=zdl[u];
                q.push({v,dis[v]});
            }
        }
    }
    
}
int main(){
    ios::sync_with_stdio(0);
    memset(dis,0x3f,sizeof(dis));
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,1});
        adj[v].push_back({u,1});
    }
    dijk();
    for(int i=1;i<=n;i++){
        cout<<zdl[i]<<endl;
    }
    return 0;
}