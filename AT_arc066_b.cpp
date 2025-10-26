#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=1e9+7;
int n;
map<int,int> f;

int dfs(int u){
    if(f[u]!=0) return f[u]; 
    return f[u]=(dfs(u/2)+dfs((u-1)/2)+dfs((u-2)/2))%MOD;
}

signed main(){
    cin>>n;
    f[0]=1,f[1]=2;
    cout<<dfs(n);

    return 0;
}