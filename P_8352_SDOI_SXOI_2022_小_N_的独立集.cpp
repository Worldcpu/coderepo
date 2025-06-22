#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1520,NK=MN*5,MK=6,MOD=1e9+7;
int n,K,f[MN][NK][MK],tmp[NK][MK],siz[MN];
vector<int> adj[MN];

void dfs(int u,int pre){
    siz[u]=1;
    for(int i=1;i<=K;i++){
        f[u][0][i]=1;
    }
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        memset(tmp,0,sizeof(tmp));
        for(int i=0;i<=K*siz[u];i++){
            for(int j=0;j<=K;j++){
                if(f[u][i][j]){
                    for(int k=0;k<=K*siz[v];k++){
                        for(int p=0;p<=K;p++){
                            if(f[v][k][p]){
                                (tmp[i+p+k][max(i+k+j,i+p+k)-(i+p+k)]+=f[u][i][j]*f[v][k][p])%=MOD;
                            }
                        }
                    }
                }
            }
        }
        memcpy(f[u],tmp,sizeof(tmp));
        siz[u]+=siz[v];
    }
}

signed main(){
    freopen("2.in","r",stdin);
    freopen("ans.out","w",stdout);
    cin>>n>>K;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n*K;i++){
        int ans=0;
        for(int j=0;j<=min(i,K);j++){
            (ans+=f[1][i-j][j])%=MOD;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
