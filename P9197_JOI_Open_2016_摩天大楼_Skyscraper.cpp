#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=110,MM=1145,MOD=1e9+7;
int n,l,f[MN][MN][MM][3],a[MN];

signed main(){
    cin>>n>>l;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    f[0][0][0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            for(int k=0;k<=l;k++){
                for(int p=0;p<3;p++){
                   int pt=k+(a[i+1]-a[i])*(2*j-p),t=f[i][j][k][p];
                    if(!t) continue;
                    if(pt>l) continue;
                    f[i+1][j+1][pt][p]=(f[i+1][j+1][pt][p]+t*(j+1-p))%MOD;
                    if(j>=2){
                        f[i+1][j-1][pt][p]=(f[i+1][j-1][pt][p]+t*(j-1))%MOD;

                    }
                    if(j>=1) f[i+1][j][pt][p]=(f[i+1][j][pt][p]+t*(2*j-p))%MOD;
                    if(p<2) f[i+1][j+1][pt][p+1]=(f[i+1][j+1][pt][p+1]+t*(2-p))%MOD;
                    if(p<2&&j>=1) f[i+1][j][pt][p+1]=(f[i+1][j][pt][p+1]+t*(2-p))%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=l;i++) ans=(ans+f[n][1][i][2])%MOD;
    cout<<(n==1?1:ans);
    return 0;
}
