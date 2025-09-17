#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=620,MOD=1e9+7;
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
    cin>>n>>m>>t;
    n--;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        --u,--v;
        if(!t){
            a[u][v]=(a[u][v]-w+MOD)%MOD;
            a[v][u]=(a[v][u]-w+MOD)%MOD;
            a[u][u]=(a[u][u]+w+MOD)%MOD;
            a[v][v]=(a[v][v]+w+MOD)%MOD;
        }else{
            a[v][v]=(a[v][v]+w)%MOD;
            a[v][u]=(a[v][u]-w+MOD)%MOD;
        }
    }
    cout<<HLS::solve();
    return 0;
}