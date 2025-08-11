#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=520;
struct Edge{
    int v,w;
};
int n,x,sum,col[MN];
ll ans=0x3f3f3f3f3f3f3f3f;
short f[MN][MN][MN];
short g[MN][MN];
int dis[MN][MN];

int head[MN],nxt[MN<<1],to[MN<<1],ww[MN<<1],tot;
inline void add(int u,int v,int w){
    to[tot]=v; ww[tot]=w; nxt[tot]=head[u]; head[u]=tot++;
}

namespace Tree{
    short dfn[MN],dtot;
    short siz[MN];

    void getdis(int u,int pre,int rt,int nowdis){
        if(rt==1) dfn[u]=++dtot;
        dis[rt][u]=nowdis;
        for(int i=head[u];~i;i=nxt[i]){
            int v=to[i],w=ww[i];
            if(v==pre) continue;
            getdis(v,u,rt,nowdis+w);
        }
    }

    void dfs(int u,int pre){
        f[u][1][dfn[u]]=1-col[u];
        siz[u]=1;
        for(int i=1;i<=n;i++){
            if(i==u||dis[u][i]>x) continue;
            f[u][0][dfn[i]]=0;
        }
        for(int i=head[u];~i;i=nxt[i]){
            int v=to[i],w=ww[i];
            if(v==pre) continue;
            dfs(v,u);
            for(int i=0;i<=siz[u]+siz[v];i++)
                for(int j=1;j<=n;j++) g[i][j]=0x3f3f;
            for(int i=0;i<=siz[v];i++){
                auto mn=*min_element(f[v][i]+dfn[v],f[v][i]+dfn[v]+siz[v]);
                for(int j=0;j<=siz[u];j++){
                    for(int k=1;k<=n;k++){
                        g[i+j][k]=min((int)g[i+j][k],f[u][j][k]+f[v][i][k]);
                        if(k>=dfn[v]&&k<dfn[v]+siz[v]) continue;
                        g[i+j][k]=min((int)g[i+j][k],f[u][j][k]+mn);
                    }
                }
            }
            for(int i=0;i<=siz[u]+siz[v];i++)
                for(int j=1;j<=n;j++)
                    f[u][i][j]=g[i][j];
            siz[u]+=siz[v];
        }
    }
}

int main(){
    cin>>n>>x;
    memset(f,0x3f,sizeof(f));
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
        cin>>col[i];
        sum+=col[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        add(u,v,w); add(v,u,w);
    }
    for(int i=1;i<=n;i++){
        Tree::getdis(i,0,i,0);
    }
    Tree::dfs(1,0);
    ans=x;
    for(int i=1;i<=sum;i++)
        for(int j=1;j<=n;j++)
            ans=min(ans,1ll*f[1][i][j]);
    if(ans==x) cout<<-1;
    else cout<<ans;
    return 0;
}
