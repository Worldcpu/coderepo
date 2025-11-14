#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,MOD=1e9+7;
int f[MN],n,sum;


signed main(){
    cin>>n;
    f[n]=n;
    f[n-1]=n*n%MOD;
    for(int i=n-2;i>=1;i--){
        sum=(sum+f[i+3])%MOD;
        f[i]=f[i+1];
        f[i]=(f[i]+(n-1)*(n-1)%MOD)%MOD;
        f[i]=(f[i]+sum+i+1)%MOD;
    }
    cout<<f[1];

    return 0;
}