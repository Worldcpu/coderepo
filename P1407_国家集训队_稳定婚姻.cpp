#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m;
unordered_map<string,int> bel;
vector<int> adj[MN];

namespace Tarjan{
    int dfn[MN],low[MN],col[MN],s[MN],top,vdcc,dtot;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        s[++top]=u;
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
            int p;
            vdcc++;
            do{
                p=s[top--];
                col[p]=vdcc;
                vis[p]=0;
            }while(p!=u);
        }
    }

}using namespace Tarjan;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string x,y;
        cin>>x>>y;
        bel[x]=i,bel[y]=i+n;
        adj[bel[x]].push_back(bel[y]);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        string x,y;
        cin>>x>>y;
        adj[bel[y]].push_back(bel[x]);
    }
    for(int i=1;i<=2*n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++){
        if(col[i]==col[i+n]) cout<<"Unsafe\n";
        else cout<<"Safe\n";
    }

    return 0;
}
