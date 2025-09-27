#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f3f3f3f3f;
int n,w,a[MN],dtot,b[MN],id[MN];

namespace FYDinic{
    struct Edge{
        int v,w,c,id;
    };
    int S=MN-3,T=MN-2,mncst,dis[MN],cur[MN];
    bool vis[MN];
    vector<Edge> adj[MN];

    void add(int u,int v,int w,int c){
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,w,c,vs});
        adj[v].push_back({u,0,-c,us});
    }

    bool spfa(int S,int T){
        queue<int> q;
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        q.push(S);
        dis[S]=0;
        vis[S]=1;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(auto e:adj[u]){
                if(e.w&&dis[e.v]>dis[u]+e.c){
                    dis[e.v]=dis[u]+e.c;
                    if(!vis[e.v]){
                        q.push(e.v);
                        vis[e.v]=1;
                    }
                }
            }
        }
        memset(cur,0,sizeof(cur));
        return (dis[T]!=INF);
    }

    int dfs(int u,int lim,int T){
        if(u==T) return lim;
        vis[u]=1;
        int ret=0;
        for(int &i=cur[u];i<adj[u].size();i++){
            int v=adj[u][i].v;
            if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].c){
                int p=dfs(v,min(lim,adj[u][i].w),T);
                if(p){
                    adj[u][i].w-=p;
                    adj[v][adj[u][i].id].w+=p;
                    ret+=p;
                    lim-=p;
                    mncst+=p*adj[u][i].c;
                    if(!lim) break;
                }else dis[v]=INF;
            }
        }
        vis[u]=0;
        return ret;
    }

    int dinic(int S,int T){
        int ans=0,flow;
        mncst=0;
        while(spfa(S,T)){
            while(flow=dfs(S,INF,T)) ans+=flow;
        }
        return ans;
    }
}using namespace FYDinic;

void cdq(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    cdq(l,mid),cdq(mid+1,r);
    for(int i=l;i<=r;i++){
        b[i]=a[i];
        id[i]=++dtot;
    }
    sort(b+l,b+r+1);
    for(int i=l;i<r;i++){
        add(id[i+1],id[i],INF,b[i+1]-b[i]);
        add(id[i],id[i+1],INF,b[i+1]-b[i]);
    }
    for(int i=l;i<=r;i++){
        int t=lower_bound(b+l,b+r+1,a[i])-b;
        if(i<=mid) add(i+n,id[t],1,0);
        else add(id[t],i,1,0);
    }
}

signed main(){
    cin>>n>>w;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        add(S,i,1,w);
        add(i,T,1,0);
        add(S,i+n,1,0);
    }
    dtot=2*n+1;
    cdq(1,n);
    dinic(S,T);
    cout<<mncst;
    return -1;
}