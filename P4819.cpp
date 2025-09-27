#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,m,in[MN],pcnt;
double ans;
vector<int> adj[MN],G[MN];
map<pir,bool> mp;

namespace Tarjan{
    int dfn[MN],low[MN],bel[MN],vtot,dtot,st[MN],top,siz[MN];
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]) low[u]=min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u]){
            vtot++;
            int p;
            do{
                p=st[top--];
                vis[p]=0;
                bel[p]=vtot;
                siz[vtot]++;
            }while(p!=u);
        }
    }

}using namespace Tarjan;

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=n;i++){
        for(auto v:adj[i]){
            if(bel[i]!=bel[v]&&!mp[pir(bel[i],bel[v])]){
                mp[pir(bel[i],bel[v])]=1;
                in[bel[v]]++;
                G[bel[i]].push_back(bel[v]);
            }
        }
    }
    ans=1;
    bool flag=0;
    for(int i=1;i<=vtot;i++){
        if(!in[i]){
            pcnt++;
            if(!flag&&siz[i]==1){
                bool flg=1;
                for(auto v:G[i]){
                    if(in[v]<2){
                        flg=0;
                        break;
                    }
                }
                if(flg){
                    flag=1;
                    pcnt--;
                }
            }
        }
    }
    ans=1-1.0*pcnt/n;
    cout<<fixed<<setprecision(6)<<ans;

    return 0;
}