#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int m,n,cut[MN],ans1,ans2;
vector<int> adj[MN],G[MN];

namespace YFTree{
    int dfn[MN],low[MN],s[MN],top,dtot,ftot;

    void tarjan(int u){
        int son=0;
        low[u]=dfn[u]=++dtot;
        s[++top]=u;
        for(auto v:adj[u]){
            if(!dfn[v]){
                son++;
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]){
                    if(u!=1) cut[u]=1;
                    G[++ftot].push_back(u);
                    int x;
                    do{
                        x=s[top--];
                        G[ftot].push_back(x);
                    }while(x!=v);
                }
            }else low[u]=min(low[u],dfn[v]);
        }
        if(u==1&&son>1) cut[1]=1;
    }

}

void init(){
    YFTree::top=0;
    YFTree::dtot=0;
    for(int i=1;i<=n;i++){
        YFTree::dfn[i]=YFTree::low[i]=cut[i]=0;
        adj[i].clear();
    }
    for(int i=n+1;i<=YFTree::ftot;i++) G[i].clear();
    n=0;
}

void solve(){
    init();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        n=max({n,u,v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    YFTree::ftot=n;
    YFTree::tarjan(1);
    if(YFTree::ftot==n+1){
        cout<<2<<" "<<n*(n-1)/2<<'\n';
        return;
    }
    ans1=0,ans2=1;
    for(int i=n+1;i<=YFTree::ftot;i++){
        int cnt=0;
        for(auto v:G[i]){
            cnt+=cut[v];
        }
        if(cnt==1){
            ans1++;
            ans2=ans2*(G[i].size()-1);
        }
    }
    cout<<ans1<<" "<<ans2<<'\n';
}

signed main(){
    int tot=0;
    while(1){
        cin>>m;
        if(!m) break;
        cout<<"Case "<<++tot<<": ";
        solve();
    }
    return 0;
}