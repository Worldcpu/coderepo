#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e4+15;
int n,fib[520],sum[520];
map<int,int> mp[MN];
int dfs(int n,int m){
    if(n<0) return 0;
    if(!n||!m) return !n?1:0;
    if(mp[m].count(n)) return mp[m][n];
    if(n>=sum[m-1]){
        return mp[m][n]=dfs(n-fib[m],m-1);
    }
    return mp[m][n]=dfs(n,m-1)+dfs(n-fib[m],m-1);
}

signed main(){
    cin>>n;
    fib[1]=sum[1]=1;
    for(int i=2;i<=88;i++){
        fib[i]=fib[i-1]+fib[i-2];
        sum[i]=sum[i-1]+fib[i];
    }
    cout<<dfs(n,88);
    return 0;
}
