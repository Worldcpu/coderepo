#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
constexpr int INF=0x3f3f3f3f;
struct Query{
    int u1,v1,u2,v2,w;
}qry[MN];
int n,m,st,qtot,dis[MN],pre[MN];
bool vis[MN];
vector<pir> adj[MN],g[MN];

namespace Tree{
    int dep[MN],fa[MN][20],dtot;
    int in[MN][20],out[MN][20];

    void dfs(int u,int pre){
        dep[u]=dep[pre]+1;
        fa[u][0]=pre;
        in[u][0]=++dtot;
        adj[dtot].push_back({u,0});
        adj[dtot].push_back({pre,0});
        out[u][0]=++dtot;
        adj[u].push_back({dtot,0});
        adj[pre].push_back({dtot,0});
        for(int j=0;j<__lg(n);j++){
            fa[u][j+1]=fa[fa[u][j]][j];
            in[u][j+1]=++dtot;
            adj[dtot].push_back({in[u][j],0});
            adj[dtot].push_back({in[fa[u][j]][j],0});
            out[u][j+1]=++dtot;
            adj[out[u][j]].push_back({dtot,0});
            adj[out[fa[u][j]][j]].push_back({dtot,0});
        }
        for(auto e:g[u]){
            int v=e.first;
            if(v==pre) continue;
            dfs(v,u);
        }
    }

    void lca1(int x,int y,int k){
        if(dep[x]<dep[y]) swap(x,y);
        adj[y].push_back({k,0});
        for(int i=__lg(n);i>=0;i--){
            if(dep[fa[x][i]]>=dep[y]){
                adj[out[x][i]].push_back({k,0});
                x=fa[x][i];
            }
        }
        if(x==y) return;
        for(int i=__lg(n);i>=0;i--){
            if(fa[x][i]!=fa[y][i]){
                adj[out[x][i]].push_back({k,0});
                adj[out[y][i]].push_back({k,0});
                x=fa[x][i];
                y=fa[y][i];
            }
        }
        adj[out[x][0]].push_back({k,0});
    }

    void lca2(int x,int y,int k){
        if(dep[x]<dep[y]) swap(x,y);
        adj[k].push_back({y,0});
        for(int i=__lg(n);i>=0;i--){
            if(dep[fa[x][i]]>=dep[y]){
                adj[k].push_back({in[x][i],0});
                x=fa[x][i];
            }
        }
        if(x==y) return;
        for(int i=__lg(n);i>=0;i--){
            if(fa[x][i]!=fa[y][i]){
                adj[k].push_back({in[x][i],0});
                adj[k].push_back({in[y][i],0});
                x=fa[x][i];
                y=fa[y][i];
            }
        }
        adj[k].push_back({in[x][0],0});
    }
}using namespace Tree;

int root(int x){
    return pre[x]==x?x:pre[x]=root(pre[x]);
}

void dijk(int st){
    priority_queue<pir,vector<pir>,greater<pir>> q;
    memset(dis,0x3f,sizeof(dis));
    dis[st]=0;
    q.push({0,st});
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
            int v=e.first,w=e.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push({dis[v],v});
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>st;
    dtot=n;
    for(int i=1;i<=n;i++) pre[i]=i;
    while(m--){
        int op,u1,v1,u2,v2,w;
        cin>>op;
        if(op==1){
            cin>>u1>>v1>>u2>>v2>>w;
            if(root(u1)!=root(v1)||root(u2)!=root(v2)) continue;
            qry[++qtot]={u1,v1,u2,v2,w};
        }else{
            cin>>u1>>v1>>w;
            int ru=root(u1),rv=root(v1);
            if(ru==rv) continue;
            g[u1].push_back({v1,w});
            g[v1].push_back({u1,w});
            adj[u1].push_back({v1,w});
            adj[v1].push_back({u1,w});
            pre[rv]=ru;
        }
    }
    for(int i=1;i<=n;i++)
        if(!dep[i]) dfs(i,0);
    for(int i=1;i<=qtot;i++){
        lca1(qry[i].u1,qry[i].v1,++dtot);
        lca2(qry[i].u2,qry[i].v2,++dtot);
        adj[dtot-1].push_back({dtot,qry[i].w});
    }
    dijk(st);
    for(int i=1;i<=n;i++)
        cout<<(dis[i]==INF?-1:dis[i])<<" ";
    return 0;
}
