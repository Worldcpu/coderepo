#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3520,MOD=1e9+7;
int f[MN][MN],sum[MN][MN],n;
string s;

signed main(){
    cin>>n>>s;
    s=' '+s;
    f[1][1]=1;
    for(int i=1;i<=n;i++){
        sum[1][i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(s[i-1]=='<') f[i][j]=sum[i-1][j-1]%MOD;
            else if(s[i-1]=='>') f[i][j]=(sum[i-1][i-1]-sum[i-1][j-1]+MOD)%MOD;
            sum[i][j]=(sum[i][j-1]+f[i][j])%MOD;
        }
    }
    cout<<sum[n][n];
    return 0;
}
