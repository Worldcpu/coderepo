#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int f[2][MN][MN],MOD,n,m;


signed main(){
    cin>>n>>MOD;
    for(int i=0;i<=n;i++){
        f[0][0][i]=i+1;
    }
    cout<<1<<'\n';
    int now=0,lst=1;
    for(int i=2;i<n;i++){
        now^=1,lst^=1;
        for(int j=0;j<=i;j++){
            for(int k=0;k<=n-i;k++){
                f[now][j][k]=0;
            }
        }
        for(int j=0;j<=i;j++){
            for(int k=0;k<=n-i;k++){
                int tmp=0;
                tmp+=(j+1)*(k+1)%MOD*f[lst][j][k+1]%MOD;
                tmp-=(j+1)*(k+1)%MOD*f[lst][j][k]%MOD;
                if(j) tmp+=j*(k+1)*(f[lst][j-1][k])%MOD;
                tmp-=(j+1)*(k+1)*f[lst][j][k]%MOD;
                f[now][j][k]=(tmp%MOD+MOD)%MOD;
            }
        }
        int ans=0;
        for(int j=0;j<=i;j++){
            ans=(ans+(j+1)*f[now][j][0])%MOD;
        }
        cout<<ans<<'\n';
    }
    set<int>::iterator qwq;
    return 0;
}
