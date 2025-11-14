#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int n,L,R,a[MN],b[MN],f[MN][MN],sum[MN][MN],suma[MN],sumb[MN];

int solve(int x){
    int ans=0;
    memset(f,0,sizeof(f));
    memset(sum,0,sizeof(sum));
    f[1][0]=1;
    for(int i=0;i<=n;i++){
        sum[1][i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            if(sumb[j] - suma[i] < x) continue; 
            f[i][j]=sum[i-1][min(j,i-2)];
        }
        sum[i][0]=f[i][0];
        for(int j=1;j<i;j++){
            sum[i][j]=(sum[i][j-1]+f[i][j])%MOD;
        }
    }
    for(int i=0;i<n;i++){
        ans=(ans+f[n][i])%MOD;
    }
    return ans;
}

signed main(){
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        suma[i]=suma[i-1]+a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        sumb[i]=sumb[i-1]+b[i];
    }
    cout<<(solve(sumb[n]-suma[n]-R)-solve(sumb[n]-suma[n]-L+1)+MOD)%MOD;
    return 0;
}
