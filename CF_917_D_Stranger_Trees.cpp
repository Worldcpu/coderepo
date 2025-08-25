#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=1e9+7;
int dp[MN][MN][2],tmp[MN][MN][2],n,f[MN],g[MN],pw[MN],inv[MN];
vector<int> adj[MN];


namespace Tree{
    int siz[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        dp[u][1][0]=dp[u][1][1]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            for(int i=1;i<=siz[u];i++){
                for(int j=1;j<=siz[v];j++){
                    tmp[u][i+j][0]=(tmp[u][i+j][0]+dp[u][i][0]*dp[v][j][1])%MOD;
                    tmp[u][i+j][1]=(tmp[u][i+j][1]+dp[u][i][1]*dp[v][j][1])%MOD;
                    tmp[u][i+j-1][0]=(tmp[u][i+j-1][0]+dp[u][i][0]*dp[v][j][0])%MOD;
                    tmp[u][i+j-1][1]=(tmp[u][i+j-1][1]+dp[u][i][0]*dp[v][j][1]+dp[u][i][1]*dp[v][j][0])%MOD;
                }
            }
            siz[u]+=siz[v];
            for(int i=1;i<=siz[u];i++){
                dp[u][i][0]=tmp[u][i][0];
                dp[u][i][1]=tmp[u][i][1];
                tmp[u][i][0]=tmp[u][i][1]=0;
            }
        }

    }

}using namespace Tree;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++)  pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=2;i<=n;i++){
        g[n-i]=dp[1][i][1]*ksm(n,i-2)%MOD;
    }
    g[n-1]=1;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int ret=g[j]*getC(j,i)%MOD;
            if((j-i)&1){
                g[i]=(g[i]-ret+MOD)%MOD;
            }else{
                g[i]=(g[i]+ret)%MOD;
            }
        }
        cout<<g[i]<<' ';
    }

    return 0;
}