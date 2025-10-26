#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15,MV=1e9;
constexpr int INF=5e18;
struct Edge{
    int v,w;
};
struct EDGE{
    int u,v,w,delw;
}e[MN];
int n,m,ltot,q;
vector<Edge> adj[MN],fadj[MN];

struct Line{
    int k,b;

    Line(int kk=0,int bb=0){
        k=kk,b=bb;
    }

    int get(int x){
        return k*x+b;
    }
}ln[MN];

struct LCSegment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson;
        Line val;
    }t[MN*50];
    int tot,rt;

    void init(){
        tot=0;
        rt=0;
    }

    void update(int &p,int l,int r,Line k){
        if(!p){
            p=++tot;
            t[p].val=k;
            t[p].lson=t[p].rson=0;
            return;
        }
        int mid=(l+r)>>1;
        if(k.get(mid)<t[p].val.get(mid)) swap(t[p].val,k);
        if(l==r) return;
        if(k.get(l)<t[p].val.get(l)) update(ls,l,mid,k);
        if(k.get(r)<t[p].val.get(r)) update(rs,mid+1,r,k);
    }

    int query(int p,int l,int r,int x){
        if(!p) return INF;
        int mid=(l+r)>>1,ret=t[p].val.get(x);
        if(l==r) return ret;
        if(mid>=x) return min(ret,query(ls,l,mid,x));
        else return min(ret,query(rs,mid+1,r,x));
    }
}sg;

namespace Dijkstra{
    int dis1[MN],disn[MN];
    bool vis[MN];

    void dijk(int st,int dis[],const vector<Edge> adj[]){
        priority_queue<pir,vector<pir>,greater<pir>> q;
        fill(dis+1,dis+1+n,INF);
        fill(vis+1,vis+1+n,0);
        q.push(pir(0,st));
        dis[st]=0;
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    q.push(pir(dis[v],v));
                }
            }
        }
    }

}using namespace Dijkstra;

void init(){
    sg.init();
    for(int i=1;i<=n;i++){
        adj[i].clear();
        fadj[i].clear();
    }
    ltot=0;

}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int u,v,w,delw;
        cin>>u>>v>>w>>delw;
        e[i]={u,v,w,delw};
        adj[u].push_back({v,w});
        fadj[v].push_back({u,w});
    }
    dijk(1,dis1,adj);
    dijk(n,disn,fadj);
    for(int i=1;i<=m;i++){
        int dis;
        dis=dis1[e[i].u]+disn[e[i].v]+e[i].w;
        if(dis1[e[i].u]<INF&&disn[e[i].v]<INF){
            ln[++ltot]=Line(-e[i].delw,dis);
        }
    }
    for(int i=1;i<=ltot;i++){
        sg.update(sg.rt,1,MV,ln[i]);
    }
    cin>>q;
    while(q--){
        int k;
        cin>>k;
        cout<<sg.query(sg.rt,1,MV,k)<<'\n';
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}