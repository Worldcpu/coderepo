#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=6e6+15,MOD=51123987,INV2=25561994;
int p[MN],f[MN],g[MN],tot,n,ans;
char s[MN],a[MN];

void manacher(){
    s[0] = '*', s[(n << 1) + 1] = '#';
    for(int i = 1; i <= n; ++i)
        s[(i << 1) - 1] = '#', s[i << 1] = a[i];
    n = (n << 1) + 1;
    int mx = 0, id = 0;
    for(int i = 1; i <= n; ++i){
        if(i < mx) p[i] = min(mx - i, p[(id << 1) - i]);
        else p[i] = 1;
        while(i - p[i] >= 1 && i + p[i] <= n && s[i - p[i]] == s[i + p[i]]) p[i]++;
        if(i + p[i] > mx) mx = i + p[i], id = i;
        tot = (tot + (p[i] >> 1)) % MOD;
    }
}

signed main(){
    scanf("%lld%s",&n,a+1);
    manacher();
    for(int i=1;i<=n;i++){
        f[i-p[i]+1]++;
        f[i+1]--;
        g[i]++;
        g[i+p[i]]--;
    }
    for(int i=1;i<=n;i++) f[i]+=f[i-1],g[i]+=g[i-1];
    ans=tot*(tot-1)/2%MOD;
    int sum=0;
    for(int i=2;i<=n-2;i+=2){
        sum=(sum+g[i])%MOD;
        ans=(ans-sum*f[i+2]%MOD+MOD)%MOD;
    }
    cout<<ans;
    return 0;
}
