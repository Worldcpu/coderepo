#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=998244353;
int f[MN],g[MN],n;
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

void dfs1(int u,int pre){
    f[u]=2;
    g[u]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        f[u]=(f[v]*2-g[v])*f[u]%MOD;
        g[u]=g[u]*f[v]%MOD;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    cout<<(ksm(2,2*n-1)-f[1]+g[1]+MOD)%MOD;
    return 0;
}