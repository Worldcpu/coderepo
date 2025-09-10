#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=120,MP=5e5+15,MOD=998244353;
int f[MN][MN][MN],tmp[MN][MN][MN],n,m,pw[MP],inv[MP],siz[MN],ans;
vector<int> adj[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MP;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MP-1]=ksm(pw[MP-1],MOD-2);
    for(int i=MP-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

void dfs(int u,int pre){
    f[u][1][0]=1;
    siz[u]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        f[v][0][1]=1;
        memset(tmp[u],0,sizeof(tmp[u]));
        for(int i=0;i<=siz[u];i++){
            for(int j=0;j<=siz[u];j++){
                for(int k=0;k<=siz[v];k++){
                    for(int p=0;p<=siz[v];p++){
                        (tmp[u][i+k][j+p]+=f[u][i][j]*f[v][k][p]%MOD)%=MOD;
                    }
                }
            }
        }
        for(int i=0;i<=siz[u]+siz[v];i++){
            for(int j=0;j<=siz[u]+siz[v];j++){
                f[u][i][j]=tmp[u][i][j];
                tmp[u][i][j]=0;
            }
        }
        siz[u]+=siz[v];
    }
}

signed main(){
    initpw();
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        for(int j=m+1;j<=siz[i];j++){
            for(int k=0;k<=siz[i];k++){
                int p=k+(i!=1);
                ans=(ans+f[i][j][k]*pw[j]%MOD*pw[p]%MOD*inv[j+p]%MOD)%MOD;
            }
        }
    }   
    cout<<ans;
    return 0;
}