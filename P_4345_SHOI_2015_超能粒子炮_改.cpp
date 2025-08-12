#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=2333;
int n,K,C[MOD+15][MOD+15],sum[MOD+15][MOD+15];

void initC(){
    for(int i=0;i<=MOD;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
        }
    }
    for(int i=0;i<=MOD;i++){
        sum[i][0]=1;
        for(int j=1;j<=MOD;j++){
            sum[i][j]=(sum[i][j-1]+C[i][j])%MOD;
        }
    }
}

int lucas(int n,int m){
    if(n<m) return 0;
    if(!m||n==m) return 1;
    return lucas(n/MOD,m/MOD)*C[n%MOD][m%MOD]%MOD;
}

int solve(int n,int k){
    if(k<0) return 0;
    if(!n||!k) return 1;
    if(n<MOD&&k<MOD) return sum[n][k];
    return (solve(n/MOD,k/MOD-1)*sum[n%MOD][MOD-1]%MOD+lucas(n/MOD,k/MOD)*sum[n%MOD][k%MOD]%MOD)%MOD;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    initC();
    int T;
    cin>>T;
    while(T--){
        cin>>n>>K;
        cout<<solve(n,K)<<'\n';
    }
    return 0;
}
