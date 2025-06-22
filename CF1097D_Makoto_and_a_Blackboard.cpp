#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int f[MN],s[MN],id,n,m,dg[MN];
vector<int> adj[MN];

signed main(){
    cin>>id>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        dg[u]++;
    }
    for(int i=1;i<=n;i++){
        f[i]=dg[i]+1;
        for(auto v:adj[i]){
            f[i]=(f[i]+(s[i-1]-s[v-1])%MOD+MOD)%MOD;
        }
        s[i]=(s[i-1]+f[i])%MOD;
    }
    cout<<s[n];
    return 0;
}
