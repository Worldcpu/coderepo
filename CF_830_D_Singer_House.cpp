#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=1e9+7;
int n,f[MN][MN];

int dfs(int u,int k){
    if(!k) return 1;
    if(u==1) return (k==1);
    if(~f[u][k]) return f[u][k];
    int ret=0;
    for(int i=0;i<=k;i++){
        ret=(ret+dfs(u-1,i)*dfs(u-1,k-i))%MOD;
    }
    for(int i=0;i<k;i++){
        ret=(ret+dfs(u-1,i)*dfs(u-1,k-i-1))%MOD;
    }
    for(int i=0;i<=k;i++){
        ret=(ret+dfs(u-1,i)*dfs(u-1,k-i)%MOD*2*k)%MOD;
    }
    for(int i=0;i<=k+1;i++){
        ret=(ret+dfs(u-1,i)*dfs(u-1,k-i+1)%MOD*k*(k+1))%MOD;
    }
    return f[u][k]=ret;
}

signed main(){
    memset(f,-1,sizeof(f));
    cin>>n;
    cout<<dfs(n,1);


    return 0;
}