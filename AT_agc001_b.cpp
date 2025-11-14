#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,x;

int dfs(int n,int m){
    if(!m){
        return -n;
    }
    return dfs(m,n%m)+(n/m)*2*m;
}

signed main(){
    cin>>n>>x;
    cout<<dfs(x,n-x)+n;
    return 0;
}