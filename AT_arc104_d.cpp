#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=102;
int n,K,MOD,f[MN][1000005],ans,sum;


signed main(){
    cin>>n>>K>>MOD;
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            f[i][j]=f[i-1][j];
        }
        sum+=i*K;
        for(int j=i;j<=sum;j++){
            f[i][j]=(f[i][j]+f[i][j-i])%MOD;
        }
        for(int j=sum;j>=i*(K+1);j--){
            f[i][j]=(f[i][j]-f[i][j-i*(K+1)]+MOD)%MOD;
        }
    }
    for(int i=1;i<=n;i++){
        ans=0;
        for(int j=0;j<=sum;j++){
            ans=(ans+(K+1)*f[i-1][j]%MOD*f[n-i][j]%MOD)%MOD;
        }
        cout<<(ans-1+MOD)%MOD<<'\n';
    }
    

    return 0;
}