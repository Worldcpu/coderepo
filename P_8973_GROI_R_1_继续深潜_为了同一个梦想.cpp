#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int MN=5e5+15;
const int MOD=1e9+7;
int n;
ll f[MN],ret[MN];
vector<int> adj[MN];
void dfs(int u,int fa){
    f[u]=1;
    for(auto v:adj[u]){
        if(v==fa)continue;
        dfs(v,u);
        f[u]+=2*f[v];
    }
    f[u]%=MOD;
}

int getans(int u){
    ll sum=0,pfsum=0;
    for(auto v:adj[u]){
        sum+=f[v];
        pfsum+=f[v]*f[v];
    }
    return (sum+(sum*sum-pfsum)/2)%MOD;
}

void dfs2(int u,int fa){
    f[u]=1;
    for(auto v:adj[u]){
        f[u]+=2*f[v];
    }
    f[u]%=MOD;
    ll fu=f[u];
    ret[u]=getans(u);
    for(auto v:adj[u]){
        if(v==fa) continue;
        f[u]=(fu-2*f[v]+2*MOD)%MOD;
        dfs2(v,u);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    dfs2(1,0);
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans^=ret[i]*i;
    }
    cout<<ans;
    return 0;
}