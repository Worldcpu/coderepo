#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+9;
int ans,fm[MN],f[MN],fc[MN],tot,T,n,p[MN];
bool vis[MN];

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
    fc[0]=1;
    for(int i=1;i<MN;i++){
        fc[i]=fc[i-1]*i%MOD;
    }
    f[1]=1;
    for(int i=2;i<MN;i++){
        f[i]=ksm(i,i-2)%MOD;
    }
}

int dfs(int u){
    vis[u]=1;
    if(vis[p[u]]) return 1;
    return dfs(p[u])+1;
}

void solve(){
    memset(vis,0,sizeof(vis));
    tot=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]) fm[++tot]=dfs(i);
    }
    ans=fc[n-tot]%MOD;
    for(int i=1;i<=tot;i++){
        ans=ans*f[fm[i]]%MOD*ksm(fc[fm[i]-1],MOD-2)%MOD;
    }
    cout<<ans<<'\n';
}

signed main(){
    init();
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
