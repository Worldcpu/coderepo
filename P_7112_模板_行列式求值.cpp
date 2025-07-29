#include<bits/stdc++.h>
using namespace std;
constexpr int MN=620;
int n,MOD,a[MN][MN];

namespace HLS{

    int solve(){
        int ret=1,w=1;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                while(a[i][i]){
                    int div=a[j][i]/a[i][i];
                    for(int k=i;k<=n;k++){
                        a[j][k]=(a[j][k]-1ll*div*a[i][k]%MOD+MOD)%MOD;
                    }
                    swap(a[i],a[j]);
                    w=-w;
                }
                swap(a[i],a[j]);
                w=-w;
            }
        }
        for(int i=1;i<=n;i++){
            ret=1ll*a[i][i]*ret%MOD;
        }
        ret=1ll*w*ret;
        return (ret+MOD)%MOD;
    }

}

int main(){
    cin>>n>>MOD;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    cout<<HLS::solve();

    return 0;
}