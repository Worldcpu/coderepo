#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Edge
{
    int v,w;
};
int n,m,q,yftot,tot,dfn[MN],sum[MN],b[MN],low[MN],fa[MN],dep[MN],depp[MN],top[MN],hson[MN],siz[MN];
vector<Edge> adj[MN],yf[MN<<1];

void solvelp(int u,int v,int w){
    yftot++;
    int i=v,prew=w;
    while(i!=fa[u]){
        sum[i]=prew;
        prew+=b[i];
        i=fa[i];
    }
    sum[yftot]=sum[u];
    sum[u]=0;
    i=v;
    while(i!=fa[u]){
        int dis=min(sum[i],sum[yftot]-sum[i]);
        yf[yftot].push_back({i,dis});
        yf[i].push_back({yftot,dis});
        i=fa[i];
    }
}

void tarjan(int u,int pre){
    low[u]=dfn[u]=++tot;
    for(auto e:adj[u]){
        if(e.v==pre) continue;
        if(!dfn[e.v]){
            fa[e.v]=u;
            b[e.v]=e.w;
            tarjan(e.v,u);
            low[u]=min(low[u],low[e.v]);
        }else low[u]=min(low[u],dfn[e.v]);
        if(low[e.v]>dfn[u]){
            yf[u].push_back({e.v,e.w});
            yf[e.v].push_back({u,e.w});
        }
    }
    for(auto e:adj[u]){
        if(fa[e.v]==u||dfn[e.v]<=dfn[u]) continue;
        solvelp(u,e.v,e.w);
    }
}

void dfs1(int u,int pre){
    siz[u]=1;
    fa[u]=pre;
    depp[u]=depp[pre]+1;
    int maxp=-1;
    for(auto e:yf[u]){
        if(e.v==pre) continue;
        dep[e.v]+=dep[u]+e.w;
        dfs1(e.v,u);
        siz[u]+=siz[e.v];
        if(maxp<siz[e.v]){
            hson[u]=e.v;
            maxp=siz[e.v];
        }
    }
}

void dfs2(int u,int ltop){
    top[u]=ltop;
    if(!hson[u]) return;
    dfs2(hson[u],ltop);
    for(auto e:yf[u]){
        if(e.v==fa[u]||e.v==hson[u]) continue;
        dfs2(e.v,e.v);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(depp[top[x]]<depp[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return depp[x]<depp[y]?x:y;
}

int getson(int x,int rt){
    int ret=0;
    while(top[x]!=top[rt]){
        ret=top[x];
        x=fa[top[x]];
    }
    return x==rt?ret:hson[rt];
}

int main(){
    cin>>n>>m>>q;
    yftot=n;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    tarjan(1,0);
    dfs1(1,0);
    dfs2(1,1);

    while(q--){
        int u,v;
        cin>>u>>v;
        int lcuv=lca(u,v);
        if(lcuv<=n){
            cout<<dep[u]+dep[v]-dep[lcuv]*2<<'\n';
        }else{
            int su=getson(u,lcuv),sv=getson(v,lcuv);
            if(sum[su]<sum[sv]) swap(su,sv);
            cout<<dep[u]+dep[v]-dep[su]-dep[sv]+min(sum[su]-sum[sv],sum[lcuv]-(sum[su]-sum[sv]))<<'\n';
        }
    }

    return 0;
}