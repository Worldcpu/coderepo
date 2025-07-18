#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,m,ans,num,siz[MN];
bool vis[MN];
vector<int> adj[MN],G[MN];

namespace YFTree{
    int dfn[MN],low[MN],s[MN],cnt[MN],top,dtot,ftot;

    void init(){
        ftot=n;
    }

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        s[++top]=u;
        num++;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]==dfn[u]){
                    ++ftot;
                    cnt[ftot]=0;
                    int p;
                    while(p!=v){
                        p=s[top--];
                        G[ftot].push_back(p);
                        G[p].push_back(ftot);
                        cnt[ftot]++;
                    }
                    G[ftot].push_back(u);
                    G[u].push_back(ftot);
                    cnt[ftot]++;
                }
            }else low[u]=min(low[u],dfn[v]);
        }
    }

}using namespace YFTree;

void dfs(int u,int pre){
    vis[u]=1;
    siz[u]=u<=n;
    for(auto v:G[u]){
        if(v==pre) continue;
        dfs(v,u);
        ans+=2ll*cnt[u]*siz[u]*siz[v];
        siz[u]+=siz[v];
    }
    ans+=2ll*cnt[u]*siz[u]*(num-siz[u]);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cnt[i]=-1;
    init();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            num=0;
            tarjan(i);
            top--;
            dfs(i,0);
        }
    }
    cout<<ans;
    return 0;
}
