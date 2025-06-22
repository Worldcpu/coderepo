#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int pw[MN],inv[MN],f[MN][MN],tmp[MN],siz[MN][2],n;
vector<int> adj[MN];
string s;

void dfs(int u,int pre){
    siz[u][0]=1,siz[u][1]=(s[u]-'0');
    f[u][0]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        for(int i=0;i<=siz[u][0]+siz[v][0];i++) tmp[i]=0;
        for(int i=0;i<=min(siz[u][0],n/2);i++){
            for(int j=0;j<=min(siz[v][0],n/2-i);j++){
                tmp[i+j]=(tmp[i+j]+f[u][i]*f[v][j]%MOD)%MOD;
            }
        }
        for(int i=0;i<=siz[u][0]+siz[v][0];i++) f[u][i]=tmp[i];
        siz[u][0]+=siz[v][0];
        siz[u][1]+=siz[v][1];
    }
    for(int i=min(siz[u][1],siz[u][0]-siz[u][1]);i>=1;i--){
        if(s[u]=='1'){
            f[u][i]=(f[u][i]+f[u][i-1]*(siz[u][0]-siz[u][1]-(i-1))%MOD)%MOD;
        }else{
            f[u][i]=(f[u][i]+f[u][i-1]*(siz[u][1]-(i-1))%MOD)%MOD;
        }
    }
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    init();
    cin>>n>>s;
    s=" "+s;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=0;i<=n/2;i++) f[1][i]=f[1][i]*pw[n/2-i]%MOD;
    for(int i=0;i<=n/2;i++){
        int ans=0;
        for(int j=i;j<=n/2;j++){
            int ret=getC(j,i)*f[1][j]%MOD;
            if((j-i)&1) ans=(ans-ret+MOD)%MOD;
            else ans=(ans+ret)%MOD;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
