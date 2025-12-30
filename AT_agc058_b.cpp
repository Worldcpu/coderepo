#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int L[MN],R[MN],n,p[MN],sum[MN][MN],f[MN][MN];


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        L[i]=R[i]=i;
        while(L[i]>1&&p[L[i]-1]<=p[i]) L[i]--;
        while(R[i]<n&&p[R[i]+1]<=p[i]) R[i]++;
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++) sum[0][i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i>=L[j]&&i<=R[j]){
                f[i][j]=sum[i-1][j];
            }
            sum[i][j]=(sum[i][j-1]+f[i][j])%MOD;
        }
    }
    cout<<sum[n][n];
    return 0;
}