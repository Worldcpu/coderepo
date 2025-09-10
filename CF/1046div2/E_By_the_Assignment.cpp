#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,m,V,a[MN],coll[MN],ans;
vector<int> adj[MN];

namespace Tarjan{
    int dfn[MN],low[MN],st[MN],dtot,top,bcol[MN],vdcc;
    vector<int> bel[MN];

    void tarjan(int u,int fa){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v,u);
                low[u]=min(low[u],low[v]);
            }else if(v!=fa){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(dfn[u]==low[u]){
            vdcc++;
            int x;
            do{
                x=st[top--];
                bcol[x]=vdcc;
                bel[vdcc].push_back(x);
            }while(x!=u);
        }
    }

}using namespace Tarjan;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    ans=1;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        bel[i].clear();
        low[i]=dfn[i]=bcol[i]=st[i]=0;
        coll[i]=-1;
    }
    top=vdcc=top=dtot=0;
}

int dfs(int u,int pre,int col){
    if(~coll[u]) return coll[u]==col;
    coll[u]=col;
    for(auto v:adj[u]){
        if(v==pre) continue;
        if(bcol[u]==bcol[v]){
            int ret=dfs(v,u,!col);
            if(!ret) return 0;
        }
    }
    return 1;
}

void solve(){
    cin>>n>>m>>V;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i,0);
    }
    for(int i=1;i<=vdcc;i++){
        int ret=-1;
        for(auto v:bel[i]){
            if(a[v]<0) continue;
            else if(ret<0) ret=a[v];
            else if(ret!=a[v]){
                cout<<0<<'\n';
                return;
            }
        }
        auto dret=dfs(bel[i][0],0,0);
        if(dret&&ret==-1){
            ans=ans*V%MOD;
        }
        if(!dret&&ret>0){
            cout<<0<<'\n';
            return;
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--) solve();

    return 0;
}