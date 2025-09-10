#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e4+15,MB=256,MP=8;
int n,q,a[MN],g[MN][MB+15],f[MN][MB+15],val[MN][MB+15];
vector<int> adj[MN];
struct Trie{
    int t[600][2],tot;
    Trie(){tot=1;}
    void init(){for(int i=0;i<=tot;i++)t[i][0]=t[i][1]=0;tot=1;}
    void insert(int x){int p=1;for(int i=MP-1;i>=0;i--){int k=(x>>i)&1;if(!t[p][k])t[p][k]=++tot;p=t[p][k];}}
    int query(int x){int p=1,ret=0;for(int i=MP-1;i>=0;i--){int nk=(x>>i)&1;if(!t[p][nk^1])p=t[p][nk];else{p=t[p][nk^1];ret+=(1<<i);}}return ret;}
}t;
namespace Tree{
    int dep[MN],fa[MN],st[MN],bef[MN],top;
    void dfs1(int u,int pre){
        st[++top]=u;fa[u]=pre;dep[u]=dep[pre]+1;
        if(dep[u]>=MB){
            bef[u]=st[top-MB];
            for(int i=top;i>=top-MB+1;i--)t.insert(a[st[i]]>>MP);
            for(int i=0;i<MB;i++)val[u][i]=t.query(i)<<MP;
            for(int i=top,j=0;i>=MB;i-=MB,j++)f[u][j]=val[st[top-j*MB]][j];
            t.init();
        }
        for(auto v:adj[u])if(v!=pre)dfs1(v,u);
        top--;
    }
    void dfs2(int u,int pre){
        st[++top]=u;
        if(dep[u]>=MB){
            for(int i=top,j=0;i>=top-MB+1;i--,j++){
                int hi=(a[st[i]]>>MP);
                g[u][hi]=max(g[u][hi],(j^a[st[i]])&(MB-1));
            }
            for(int i=dep[u],j=0;i>=MB;i-=MB,j++){
                int now=(f[u][j]>>MP)^j;
                f[u][j]+=g[st[top-j*MB]][now];
            }
        }
        for(auto v:adj[u])if(v!=pre)dfs2(v,u);
        top--;
    }
}using namespace Tree;
signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<n;i++){int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);}
    dfs1(1,0);dfs2(1,0);
    while(q--){
        int x,y;cin>>x>>y;
        int now=y,cnt=0,ret=0;
        while(dep[now]-dep[x]>=MB){now=bef[now];cnt++;}
        for(int i=0;i<cnt;i++)ret=max(ret,f[y][i]);
        while(1){ret=max(ret,a[now]^(dep[y]-dep[now]));if(now==x)break;now=fa[now];}
        cout<<ret<<'\n';
    }
    return 0;
}
