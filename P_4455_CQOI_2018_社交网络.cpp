#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=620,MOD=1e4+7;
int n,m,t,a[MN][MN];

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

signed main(){
    cin>>n>>m;
    n--;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        --u,--v;
        a[u][v]=(a[u][v]-1+MOD)%MOD;
        a[u][u]=(a[u][u]+1)%MOD;
    }
    cout<<HLS::solve();
    return 0;
}