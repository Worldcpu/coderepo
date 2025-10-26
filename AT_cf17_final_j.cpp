#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
const long long LINF = (long long)1e18; 
struct Edge{
    int v,w;
};
int n;
int a[MN];
long long ans;
long long cst2[MN];
pir lk2[MN];
vector<Edge> adj[MN];

struct QWQ{
    int x,col;
    long long dis;

    QWQ(int xx=0,int coll=0,long long diss=LINF){
        x=xx; col=coll; dis=diss;
    }
};

struct Node{
    QWQ fir,sec;

    Node(QWQ firr=QWQ(),QWQ secc=QWQ()){
        fir=firr; sec=secc;
    }

    friend Node operator*(const Node &x,const QWQ &y){
        auto ret=Node(x.fir,x.sec);
        if(ret.fir.col==y.col){
            ret.fir.dis=min(ret.fir.dis,y.dis);
        }else if(ret.sec.col==y.col){
            ret.sec.dis=min(ret.sec.dis,y.dis);
            if(ret.sec.dis<ret.fir.dis) swap(ret.fir,ret.sec);
        }else if(y.dis<=ret.fir.dis){
            ret.sec=ret.fir;
            ret.fir=y;
        }else if(y.dis<ret.sec.dis){
            ret.sec=y;
        }
        return ret;
    }

    friend Node operator+(const Node &x,const Node &y){
        return (y * x.fir) * x.sec;
    }
}f[MN];

namespace DSU{
    int pree[MN];
    void initpre(){
        for(int i=1;i<=n;i++) pree[i]=i;
    }
    int root(int x){
        if(pree[x]==x) return x;
        return pree[x]=root(pree[x]);
    }
} using namespace DSU;

namespace Tree{
    int sumv[MN], fa[MN], col[MN], lk[MN];
    long long cst[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        if(pre==0) sumv[u]=0;
        a[u]+=sumv[u];
        for(auto e:adj[u]){
            int v=e.v;
            if(v==pre) continue;
            sumv[v]=sumv[u]+e.w;
            dfs1(v,u);
        }
    }

    void dfs2(int u,int pre){
        f[u]=Node(QWQ(u,col[u],a[u]), QWQ(0,0,LINF));
        for(auto e:adj[u]){
            int v=e.v;
            if(v==pre) continue;
            dfs2(v,u);
            f[u]=f[u]+f[v];
        }
    }

    void dfs3(int u,int pre){
        if(u==1){
            f[u].fir.dis -= 2LL * sumv[u];
            f[u].sec.dis -= 2LL * sumv[u];
        }
        if(f[u].fir.col == col[u]){
            lk[u] = f[u].sec.x;
            cst[u] = a[u] + f[u].sec.dis;
        } else {
            lk[u] = f[u].fir.x;
            cst[u] = a[u] + f[u].fir.dis;
        }
        for(auto e:adj[u]){
            int v=e.v;
            if(v==pre) continue;
            f[v].fir.dis -= 2LL * sumv[v];
            f[v].sec.dis -= 2LL * sumv[v];
            f[v] = f[v] + f[u];
            dfs3(v,u);
        }
    }
} using namespace Tree;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    initpre();
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v,w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs1(1,0);
    while(true){
        for(int i=1;i<=n;i++) col[i]=root(i);
        bool flag = true;
        for(int i=2;i<=n;i++) if(col[i]!=col[1]){ flag=false; break; }
        if(flag) break;
        dfs2(1,0);
        dfs3(1,0);
        for(int i=1;i<=n;i++) cst2[i]=LINF;
        for(int i=1;i<=n;i++){
            if(cst[i] < cst2[col[i]]){
                lk2[col[i]] = pir(i, lk[i]);
                cst2[col[i]] = cst[i];
            }
        }
        for(int i=1;i<=n;i++){
            if(cst2[i] < LINF){
                int x = lk2[i].first, y = lk2[i].second;
                int rx = root(x), ry = root(y);
                if(rx != ry){
                    pree[rx] = ry;
                    ans += cst2[i];
                }
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
