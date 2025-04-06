#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int MN=1e5+15;
const ll INF=1e18;
template<typename type>
inline void read(type &x)
{
    x=0;bool flag=0;char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
int T;
struct edge{
    int v;
    ll w;
};
struct node{
    int u;
    ll w;
    bool operator <(const node& x)const{
        return w>x.w;
    }
};
int n,m;
ll val[MN],dis[MN];
vector<edge> adj[MN];
bool vis[MN];

void dij(){
    priority_queue<node> q;
    q.push({1,0});
    dis[1]=0;
    vis[1]=1;
    while (!q.empty())
    {
        node f=q.top();
        q.pop();
        int u=f.u;
        vis[u]=1;
        for(int i=0;i<adj[u].size();i++){
            edge e=adj[u][i];
            if(dis[e.v]>e.w+dis[u]&&!vis[e.v]){
                dis[e.v]=e.w+dis[u];
                q.push({e.v,dis[e.v]});
            }
        }
    }
    
}
int main(){
    ios::sync_with_stdio(0);
    read(T);
    while (T--)
    {
        read(n);
        read(m);
        // memset(vis,0,sizeof(vis));
        // memset(dis,0x3f,sizeof(dis));
        for(int i=1;i<=n;i++){
            read(val[i]);
            adj[i].clear();
            vis[i]=0;
            dis[i]=INF;
        }
        for(int i=1;i<=m;i++){
            int u,v,w;
            read(u);
            read(v);
            read(w);
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        dij();
        long long ans=0;
        bool flag=0;
        for(int i=1;i<=n;i++){
            if(dis[i]==INF){
                flag=1;
                cout<<"No Answer\n";
                break;
            }
            else ans+=val[i]*dis[i];
        }
        if(!flag) cout<<ans<<'\n';
    }
    
    return 0;
}