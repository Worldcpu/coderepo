#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN = 2e6 + 15, MOD = 998244353;

int n;
int f[MN], g[MN];

int ksm(int a, int b){
    int ret = 1;
    a %= MOD;
    while(b){
        if(b & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}

int _div(int a, int b){
    a %= MOD;
    if(a < 0) a += MOD;
    b %= MOD;
    if(b < 0) b += MOD;
    return a * ksm(b,MOD-2) % MOD;
}

signed main(){
    cin >> n;
    f[n] = g[n] = 0;  
    for(int i=n-1;i>=0;i--){
        int tmp=( ( (int)n * i % MOD ) 
                  + ( ( (n - i) * ((i * 2 + 1) % MOD) % MOD ) * f[i + 1] % MOD ) 
                  + ( ( (n - i) * (n - i - 1) % MOD ) * f[i + 2] % MOD ) ) % MOD;
        f[i]=_div(tmp, ( (int)n * n % MOD - (int)i * i % MOD + MOD ) % MOD);
        g[i]=( _div(i, n) * f[i] % MOD + _div(n - i, n) * f[i + 1] % MOD ) % MOD;
    }
    cout<<f[0]<<' '<<g[0]<<'\n';
    return 0;
}
