#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e4+15,MOD=1e9+7;
int n,d,sum1,sum2,g[MN][MN],jc[MN],inv[MN];
ll ans;
vector<int> adj[MN];

int ksm(ll a,int b){
    ll ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret%MOD;
}

void init(){
    jc[0]=1;
    for(int i=1;i<MN;i++) jc[i]=1ll*jc[i-1]*i%MOD;
    inv[MN-1]=ksm(jc[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=1ll*inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b) return 0;
    return 1ll*jc[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void dfs(int u){
    for(int i=1;i<=n;i++){
        g[u][i]=1;
    }
    for(auto v:adj[u]){
        dfs(v);
        int sum=0;
        for(int i=1;i<=n;i++){
            sum=(sum+g[v][i])%MOD;
            g[u][i]=1ll*g[u][i]*sum%MOD;
        }
    }
}

signed main(){
    init();
    cin>>n>>d;
    for(int i=2;i<=n;i++){
        int v;
        cin>>v;
        adj[v].push_back(i);
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        g[1][i]=(g[1][i]+g[1][i-1])%MOD;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            g[1][i]=(g[1][i]-1ll*g[1][j]*getC(i,j)%MOD+MOD)%MOD;
        }
    }
    sum1=sum2=1;
    for(int i=1;i<=n;i++){
        sum1=1ll*sum1*(d-i+1)%MOD;
        sum2=1ll*sum2*i%MOD;
        ans=(ans+1ll*sum1*ksm(sum2,MOD-2)%MOD*g[1][i]%MOD)%MOD;
    }
    cout<<ans%MOD;
    return 0;
}
