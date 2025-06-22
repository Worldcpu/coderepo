#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e4+15,MK=26,MOD=1e9+7;
int f[MN][MK],s[MK][MK],pw[MK],n,K;
vector<int> adj[MN];

void init(){
    pw[0]=1;
    for(int i=1;i<MK;i++) pw[i]=pw[i-1]*i%MOD;
    s[0][0]=1;
    for(int i=1;i<MK;i++){
        for(int j=1;j<=i;j++){
            s[i][j]=(s[i-1][j-1]+j*s[i-1][j]%MOD)%MOD;
        }
    }
}

void dfs1(int u,int pre){
    f[u][0]=f[u][1]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        f[u][0]=(f[u][0]+f[v][0])%MOD;
        for(int i=1;i<=K;i++){
            f[u][i]=(f[u][i]+f[v][i]+f[v][i-1])%MOD;
        }
    }
}

void dfs2(int u,int pre){
    if(pre){
        for(int i=K;i>=0;i--){
            f[u][i]=f[pre][i];
            if(i>0){
                f[u][i]=(f[u][i]+f[pre][i-1])%MOD;
                f[u][i]=(f[u][i]-f[u][i-1]*2+MOD)%MOD;
            }
            if(i>1) f[u][i]=(f[u][i]-f[u][i-2]+MOD)%MOD;
        }
    }
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs2(v,u);
    }
}

void clear(){
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++) adj[i].clear();
}

void solve(){
    clear();
    cin>>n>>K;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        u++,v++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        int ans=0;
        for(int j=0;j<=K;j++){
            ans=(ans+f[i][j]*pw[j]%MOD*s[K][j]%MOD)%MOD;
        }
        cout<<ans<<'\n';
    }
    cout<<'\n';
}

signed main(){
    ios::sync_with_stdio(0);
    init();
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
