#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MK=250,MOD=1e9+7;
int n,K,f[MN][MK],tmp[MN],ans[MN],ret,S[MK][MK],siz[MN];
vector<int> adj[MN];

void initpw(){
    S[0][0]=1;
    for(int i=1;i<=K;i++){
        for(int j=1;j<=i;j++){
            S[i][j]=(S[i-1][j-1]+S[i-1][j]*j%MOD)%MOD;
        }
    }
}

void dfs1(int u,int pre){
    f[u][0]=1;
    siz[u]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        for(int i=0;i<=min(siz[u],K);i++){
            for(int j=0;j<=min(siz[v],K);j++){
                if(i+j>K) break;
                (tmp[i+j]+=f[u][i]*f[v][j]%MOD)%=MOD;
                (ans[i+j]+=f[u][i]*f[v][j]%MOD)%=MOD;
                (tmp[i+j+1]+=f[u][i]*f[v][j]%MOD)%=MOD;
                (ans[i+j+1]+=f[u][i]*f[v][j]%MOD)%=MOD;
            }
        }
        siz[u]+=siz[v];
        for(int i=0;i<=K;i++){
            (f[u][i]+=tmp[i])%=MOD;
            (f[u][i]+=f[v][i])%=MOD;
            if(i) (f[u][i]+=f[v][i-1])%=MOD;
            tmp[i]=0;
        }
    }
}

signed main(){
    cin>>n>>K;
    initpw();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=1,pw=1;i<=K;i++){
        pw=pw*i%MOD;
        ret=(ret+S[K][i]*pw%MOD*ans[i])%MOD;
    }
    cout<<ret;
    return 0;
}