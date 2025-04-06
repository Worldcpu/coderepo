#include<iostream>
using namespace std;
const int MN=15,MK=1<<MN,MOD=1e8;
int n,m,map[MN][MN],st[MK],isok[MK],f[MN][MK],ml;
int main(){
    cin>>n>>m;
    ml=(1<<m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>map[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            st[i]=(st[i]<<1)+map[i][j];
        }
    }
    for(int i=0;i<ml;i++){
        isok[i]=((i&(i<<1))==0);
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<ml;j++){
            if(isok[j]&&((j&st[i])==j)){
                for(int k=0;k<ml;k++){
                    if(!(j&k)){
                        f[i][j]=(f[i][j]+f[i-1][k])%MOD;
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<ml;i++){
        ans=(ans+f[n][i])%MOD;
    }
    cout<<ans;
    return 0;
}