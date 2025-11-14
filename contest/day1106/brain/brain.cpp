#include <bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;

struct Edge{
    int v,w;
};
int n,m,fa[MN];
map<int,int> ew[MN];
vector<Edge> adj[MN];

namespace DSU{
    int pre1[MN],pre2[MN],siz1[MN],siz2[MN];

    void initpre(){
        iota(pre1+1,pre1+1+n,1);
        iota(pre2+1,pre2+1+n,1);
        fill(siz1+1,siz1+1+n,0);  // ✅ 初始化 siz1
        fill(siz2+1,siz2+1+n,1);
    }

    int root(int pre[],int x){
        if(pre[x]==x) return x;
        else return pre[x]=root(pre,pre[x]);
    }

    void merge1(int x,int y){
        int rx=root(pre1,x),ry=root(pre1,y);
        if(rx==ry) return;
        pre1[ry]=rx;
        siz1[rx]+=siz1[ry];
    }

    void merge2(int x,int y){
        int rx=root(pre2,x),ry=root(pre2,y);
        if(rx==ry) return;
        pre2[ry]=rx;
        siz2[rx]+=siz2[ry];

        if(fa[ry]!=0) siz1[root(pre1,fa[ry])] -= siz2[ry];
        if(fa[rx]!=0) siz1[root(pre1,fa[rx])] += siz2[ry];
    }

}using namespace DSU;

namespace Tree{
    int dep[MN];

    void dfs1(int u,int p){
        fa[u]=p;
        dep[u]=dep[p]+1;
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==p) continue;
            siz1[u]++;
            dfs1(v,u);
            if(w<=1) merge1(u,v);
            if(w<=2) merge2(u,v);
        }
    }

}using namespace Tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) adj[i].clear(), ew[i].clear(), fa[i]=0;

    initpre();

    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        ew[u][v]=ew[v][u]=w;
    }

    dfs1(1,0);

    while(m--){
        int a,b,x,y;
        cin>>a>>b>>x>>y;
        ew[a][b]--;
        ew[b][a]--;
        if(dep[a]>dep[b]) swap(a,b);

        if(ew[a][b]==1) merge1(a,b);
        else if(ew[a][b]==2) merge2(a,b);

        int ans1=0;
        if(root(pre2,x)==root(pre2,y)) ans1=1;
        else if(root(pre1,fa[root(pre2,y)])==root(pre1,x)) ans1=1;
        else if(root(pre2,y)==root(pre2,fa[root(pre1,x)])) ans1=1;

        int rx1=root(pre1,x);
        int r2x=root(pre2,x);
        int ans2 = siz1[rx1]+siz2[r2x];
        int extra=root(pre2,fa[root(pre1,x)]);
        if(r2x!=extra) ans2 += siz2[extra];

        cout<<ans1<<' '<<ans2<<'\n';
    }

    return 0;
}
