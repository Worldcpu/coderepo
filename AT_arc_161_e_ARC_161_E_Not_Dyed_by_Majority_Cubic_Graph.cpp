#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,col[MN];
mt19937 mt(random_device{}());
vector<int> adj[MN],G[MN];

namespace Tarjan{
    int dfn[MN],low[MN],bel[MN],vtot,dtot,st[MN],top;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(low[u]==dfn[u]){
            ++vtot;
            int p;
            do{
                p=st[top--];
                vis[p]=0;
                bel[p]=vtot;
            }while(p!=u);
        }
    }

    void init(int n){
        for(int i=1;i<=(n);i++) dfn[i]=low[i]=vis[i]=bel[i]=0,adj[i].clear();
        vtot=dtot=top=0;
    }

    bool check(int n){
        init(n<<1);
        for(int i=1;i<=n;i++){
            for(auto u:G[i]){
                for(auto v:G[i]){
                    if(u!=v){
                        adj[u+(col[i]^1)*n].push_back((v+col[i]*n));
                    }
                }
            }
        }
        for(int i=1;i<=(n<<1);i++){
            if(!dfn[i]) tarjan(i);
        }
        bool ok=1;
        for(int i=1;i<=n;i++){
            if(bel[i]==bel[i+n]){ ok=0; break; }
        }
        return !ok;
    }
}

void init(){
    for(int i=1;i<=n;i++){
        G[i].clear();
    }
}

void solve(){
    cin>>n;
    init();
    m=3*(n>>1);   
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    while(1){
        for(int i=1;i<=n;i++){
            col[i]=mt()&1;
        }
        if(Tarjan::check(n)){
            for(int i=1;i<=n;i++){
                if(col[i]) cout<<"B";
                else cout<<"W";
            }
            break;
        }
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}