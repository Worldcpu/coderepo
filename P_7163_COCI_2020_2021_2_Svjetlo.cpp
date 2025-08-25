#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f;
int n,ans=INF,a[MN];
vector<int> adj[MN];

namespace Tree{
    int f[MN][2][2];
    bool vis[MN];

    void init(int u){
        vis[u]=a[u];
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                f[u][i][j]=(j!=a[u])?INF:0;
            }
        }
    }

    void merge(int u,int v){
        vis[u]&=vis[v];
        if(vis[v]) return;
        int tmp[2][2]{};
        for(int i=0;i<2;i++){
            tmp[0][i]=min(
                min(f[u][0][i^1]+f[v][1][0],f[u][0][i]+f[v][1][1]+2)+2,
                min(f[u][1][i]+f[v][0][0],f[u][1][i^1]+f[v][0][1]+2)+1
            );
            tmp[1][i]=min(f[u][1][i^1]+f[v][1][0],f[u][1][i]+f[v][1][1]+2)+2;
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                f[u][i][j]=tmp[i][j];
            }
        }
    }

    void dfs1(int u,int pre){
        init(u);
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            merge(u,v);
        }
    }

    void dfs2(int u,int pree){
        int len=adj[u].size();
        vector<array<array<int,2>,2>> pre(len+1),suf(len+1);
        vector<bool> prev(len+1),sufv(len+1);
        init(u);
        for(int i=0;i<len;i++){
            for(int x=0;x<2;x++) for(int y=0;y<2;y++) pre[i][x][y]=f[u][x][y];
            prev[i]=vis[u];
            merge(u,adj[u][i]);
        }
        init(u);
        for(int i=len-1;i>=0;i--){
            for(int x=0;x<2;x++) for(int y=0;y<2;y++) suf[i][x][y]=f[u][x][y];
            sufv[i]=vis[u];
            merge(u,adj[u][i]);
        }
        ans=min(ans,f[u][0][1]);
        for(int i=0;i<len;i++){
            int v=adj[u][i];
            if(v==pree) continue;
            for(int x=0;x<2;x++) for(int y=0;y<2;y++) f[u][x][y]=INF;
            for(int i1=0;i1<2;i1++){
                for(int j1=0;j1<2;j1++){
                    for(int i2=i1^1;i2<2;i2++){
                        for(int j2=0;j2<2;j2++){
                            f[u][i1&i2][j1^j2^a[u]]=min(f[u][i1&i2][j1^j2^a[u]],pre[i][i1][j1]+suf[i][i2][j2]);
                        }
                    }
                }
            }
            vis[u]=prev[i]&sufv[i];
            dfs2(v,u);
        }
    }

}using namespace Tree;

signed main(){
    string st;
    cin>>n>>st;
    st=" "+st;
    for(int i=1;i<=n;i++) a[i]=(st[i]=='1');
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    cout<<ans<<"\n";
    return 0;
}
