#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e3+15,INF=1e18;
int ans;

struct BTree{
    int lson[MN],rson[MN],tot,rt;

    BTree(){
        memset(lson,0,sizeof(lson));
        memset(rson,0,sizeof(rson));
        tot=0;
    }

}TT;

namespace Tree{
    int lson[MN],rson[MN],st[MN],siz[MN],tot,rt;

    void build(int &p){
        p=++tot;
        char qwq;
        cin>>qwq;
        st[p]=(qwq-'0');
        if(st[p]&1) build(lson[p]);
        if(st[p]&2) build(rson[p]);
    }

    void dfs1(int u,int v,int rt1,int rt2){
        if(u==rt1||v==rt2){
            if(!rt2) rt2=v;
            v=TT.rt;
        }
        if(lson[u]){
            if(!TT.lson[v]){
                TT.lson[v]=++TT.tot;
            }
            dfs1(lson[u],TT.lson[v],rt1,rt2);
        }
        if(rson[u]){
            if(!TT.rson[v]){
                TT.rson[v]=++TT.tot;
            }
            dfs1(rson[u],TT.rson[v],rt1,rt2);
        }
    }

    void solve(int u,int dep){
        TT=BTree();
        TT.tot=TT.rt=1;
        dfs1(rt,TT.rt,u,0);
        ans=min(ans,(TT.tot-1)*2-dep);
        cerr<<lson[u]<<' '<<rson[u]<<'\n';
        if(lson[u]) solve(lson[u],dep+1);
        if(rson[u]) solve(rson[u],dep+1);
    }

}using namespace Tree;


signed main(){
    build(rt);
    ans=INF;
    solve(rt,0);
    cout<<ans;
    return 0;
}