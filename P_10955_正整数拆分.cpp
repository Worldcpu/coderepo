#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MN=4049,MOD=2147483648;
int f[MN],n;
signed main(){
    cin>>n;
    // memset(f,128,sizeof(f));
    f[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            f[j]=(f[j]+f[j-i])%MOD;
        }
    }
    cout<<(f[n]-1)%MOD;
    return 0;
}