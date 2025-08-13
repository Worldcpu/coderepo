#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,q,ftot;
map<pir,int> mp;
vector<int> adj[MN],G[MN];

namespace YFTarjan{
    int dfn[MN],low[MN],stk[MN],tp,dtot;

    void init(){
        ftot=n;
    }

    void tarjan(int u,int fa){
        low[u]=dfn[u]=++dtot;
        stk[++tp]=u;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]){
                    ftot++;
                    if(low[v]>dfn[u]) mp[minmax(u,v)]=ftot;
                    int x;
                    do{
                        x=stk[tp--];
                        G[ftot].push_back(x);
                        G[x].push_back(ftot);
                    }while(x!=v);
                    G[ftot].push_back(u);
                    G[u].push_back(ftot);
                }
            }else if(v!=fa) low[u]=min(low[u],dfn[v]);
        }
    }
}

namespace Tree{
    int fa[MN],dep[MN],siz[MN],hson[MN],htop[MN],dfn[MN],dtot;

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        siz[u]=1;
        for(auto v:G[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:G[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    bool lca(int x,int y,int c){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            if(htop[x]==htop[c]&&dep[c]<=dep[x]) return 1;
            x=fa[htop[x]];
        }
        if(dep[x]<dep[y]) swap(x,y);
        if(htop[x]==htop[c]&&dep[c]>=dep[y]&&dep[c]<=dep[x]) return 1;
        return 0;
    }


}using namespace Tree;


int main(){
    cin>>n>>m;
    YFTarjan::init();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    YFTarjan::tarjan(1,0);
    dfs1(1,0);
    dfs2(1,1);
    cin>>q;
    while(q--){
        int op,a,b,c,d;
        cin>>op;
        if(op==1){
            cin>>a>>b>>c>>d;
            auto it=mp.find(minmax(c,d));
            if(it==mp.end()) cout<<"yes\n";
            else cout<<(lca(a,b,it->second)?"no\n":"yes\n");
        }else{
            cin>>a>>b>>c;
            cout<<(lca(a,b,c)?"no\n":"yes\n");
        }
    }

    return 0;
}