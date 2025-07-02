#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7;
int n,K,siz[MN],tmp[105][2][2],f[MN][105][2][2];
vector<int> adj[MN];

void add(int &x,ll y){
    x = (x + y) % MOD;
}

void dfs(int u,int pre){
    siz[u] = 1;
    f[u][0][0][0] = 1;
    f[u][1][1][0] = 1;
    for(auto v : adj[u]){
        if(v == pre) continue;
        dfs(v, u);
        for(int i=0; i<=min(siz[u],K); i++){
            tmp[i][0][0] = f[u][i][0][0];
            tmp[i][0][1] = f[u][i][0][1];
            tmp[i][1][0] = f[u][i][1][0];
            tmp[i][1][1] = f[u][i][1][1];
            f[u][i][0][0] = f[u][i][0][1] = f[u][i][1][0] = f[u][i][1][1] = 0;
        }
        // 合并子树状态
        for(int i=0; i<=min(siz[u],K); i++){
            for(int j=0; j<=min(siz[v],K-i); j++){
                add(f[u][i+j][0][0], 1ll * tmp[i][0][0] * f[v][j][0][1]);
                
                add(f[u][i+j][0][1], 1ll * tmp[i][0][1] * 
                    (0LL + f[v][j][0][1] + f[v][j][1][1])); 
                add(f[u][i+j][0][1], 1ll * tmp[i][0][0] * f[v][j][1][1]);
                
                add(f[u][i+j][1][0], 1ll * tmp[i][1][0] * 
                    (0LL + f[v][j][0][0] + f[v][j][0][1]));
                
                add(f[u][i+j][1][1], 1ll * tmp[i][1][0] * 
                    (0LL + f[v][j][1][0] + f[v][j][1][1]));
                add(f[u][i+j][1][1], 1ll * tmp[i][1][1] * 
                    (0LL + f[v][j][0][0] + f[v][j][0][1] + f[v][j][1][0] + f[v][j][1][1]));
            }
        }
        siz[u] += siz[v];
    }
}

signed main(){
    cin >> n >> K;
    for(int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << (f[1][K][0][1] + f[1][K][1][1]) % MOD;
    return 0;
}
