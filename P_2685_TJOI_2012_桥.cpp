#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
struct Edge{
    int v,w,id;
};
int n,m,etot,ans1,ans2;
bool vise[MN];
vector<Edge> adj[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mn;
    }t[MN<<2];

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].mn=INF;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);   
        build(rs,mid+1,r);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            t[p].mn=min(k,t[p].mn);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
    }

    int query(int p,int pos){
        if(t[p].l==t[p].r) return t[p].mn;
        int mid=(t[p].l+t[p].r)>>1,ret=t[p].mn;
        if(mid>=pos) ret=min(ret,query(ls,pos));
        else ret=min(ret,query(rs,pos));
        return ret;
    }
}sg;

namespace DSU{
    int root(int x,int pre[]){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x],pre);
    }
}using namespace DSU;

namespace Dijkstra{
    int dis[2][MN],vis[MN],dfa[2][MN],dfn[MN],dtot;

    void dfs(int u,int dfa[]){
        if(u==1){
            dfn[u]=++dtot;
            return;
        }
        dfs(dfa[u],dfa);
        dfn[u]=++dtot;
    }

    void Dijk(int dis[],int dfa[],int st,int end){
        priority_queue<pir,vector<pir>,greater<pir>> q;
        for(int i=1;i<=n;i++){
            dis[i]=0x3f3f3f3f;
            vis[i]=0;
        }
        dis[st]=0;
        q.push(pir(0,st));
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+e.w){
                    dis[v]=dis[u]+e.w;
                    q.push(pir(dis[v],v));
                    dfa[v]=u;
                }
            }
        }
        if(st==1){
            dfs(end,dfa);
        }
        for(int i=1;i<=n;i++){
            if(dfn[i]) dfa[i]=i;
        }
    }
}using namespace Dijkstra;

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w,++etot});
        adj[v].push_back({u,w,++etot});
    }
    Dijk(dis[0],dfa[0],1,n);
    Dijk(dis[1],dfa[1],n,1);
    int x=1;
    while(x<n){
        for(auto e:adj[x]){
            int v=e.v,w=e.w;
            if(dis[1][v]+w==dis[1][x]){
                vise[e.id]=1;
                x=v;
                break;
            }
        }
    }
    sg.build(1,1,dtot);
    for(int i=1;i<=n;i++){
        for(auto e:adj[i]){
            int v=e.v,w=e.w,id=e.id;
            if(!vise[id]){
                int l=dfn[DSU::root(i,dfa[0])],r=dfn[DSU::root(v,dfa[1])]-1;
                if(l<=r){
                    sg.modify(1,l,r,dis[0][i]+w+dis[1][v]);
                }
            }
        }
    }
    for(int i=1;i<dtot;i++){
        int tmp=sg.query(1,i);
        if(ans1<tmp&&tmp!=INF){
            ans1=tmp;
            ans2=1;
        }else if(ans1==tmp&&tmp!=INF){
            ans2++;
        }
    }
    cout<<ans1<<' ';
    if(ans1==dis[0][n]) cout<<m;
    else cout<<ans2;
    return 0;
}
