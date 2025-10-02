#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=1000000007;
int n,ans,Ctot;
vector<int> adj[MN];


struct DPNode{
    int val,tag;

    DPNode(int v=0,int tg=1){
        val=v,tag=tg;
    }

    void dotag(int k){
        val=val*k%MOD;
        tag=tag*k%MOD;
    }
}g[MN],buf[4*MN];
DPNode *f[MN],*now=buf;

void pushdown(DPNode *it){
    if(it->tag!=1){
        (it+1)->dotag(it->tag);
        it->tag=1;
    }
}

namespace Tree{
    int hson[MN],htop[MN],dep[MN],fa[MN];

    // 修正：dep[u] 表示以 u 为根的向下最大深度（子树高度）
    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=0;
        hson[u]=0;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            if(dep[u]<dep[v]+1){
                dep[u]=dep[v]+1;
                hson[u]=v;
            }
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    void dodp(int u,int pre){
        f[u][0].val=1;
        if(hson[u]){
            f[hson[u]]=f[u]+1;
            dodp(hson[u],u);
        }
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            f[v]=now;
            now+=dep[v]+2;
            dodp(v,u);
            int len=dep[v]+1;
            if(u!=1){
                int sum=1,mul=1;
                for(int i=1;i<=len;i++){
                    pushdown(f[u]+i);
                    pushdown(f[v]+i-1);
                    sum=(sum+f[u][i].val)%MOD;
                    f[u][i].val=( (sum * f[v][i-1].val)%MOD + (mul * f[u][i].val)%MOD )%MOD;
                    mul=(mul+f[v][i-1].val)%MOD;
                }
                (f[u]+len+1)->dotag(mul);
            }else{
                int sum=1,mul=1,t=0;
                for(int i=1;i<=len;i++){
                    pushdown(f[u]+i);
                    pushdown(g+i);
                    pushdown(f[v]+i-1);
                    int to1 = ( ( (sum + t) % MOD ) * f[v][i-1].val ) % MOD;
                    to1 = ( to1 + ( mul * f[u][i].val ) % MOD ) % MOD;
                    int to2 = ( ( mul * g[i].val ) % MOD + ( (g[i].val + f[u][i].val) % MOD ) * f[v][i-1].val % MOD ) % MOD;
                    sum = (sum + f[u][i].val) % MOD;
                    mul = (mul + f[v][i-1].val) % MOD;
                    t = (t + g[i].val) % MOD;
                    f[u][i].val = to1;
                    g[i].val = to2;
                }
                (f[u]+len+1)->dotag(mul);
                (g+len+1)->dotag(mul);
            }
        }
    }

}using namespace Tree;

void init(){
    now = buf;
    fill(buf, buf+4*MN, DPNode());
    fill(g, g+n+1, DPNode());
    for(int i=0;i<=n;i++){
        adj[i].clear();
        f[i]=nullptr;
    }
    ans=1;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    f[1]=now;
    now+=dep[1]+2;
    dodp(1,0);
    for(int i=1;i<=n;i++){
        pushdown(g+i);
        ans=(ans+g[i].val)%MOD;
    }
    cout<<"Case #"<<++Ctot<<": "<<ans<<'\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
