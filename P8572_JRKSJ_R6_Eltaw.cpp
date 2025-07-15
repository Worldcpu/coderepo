#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace std;
using namespace __gnu_pbds;
constexpr int MN=750+15;
int n,K,q;
int c[MN][MN];

signed main(){
    cin>>n>>K>>q;
    int a[K+1][n+1],sum[K+1][n+1];
    for(int i=1;i<=K;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            a[i][j]+=a[i][j-1];
        }
    }
    if(n<=700){
        for(int i=1;i<=K;i++){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    c[j][k]=max(c[j][k],a[i][k]-a[i][j-1]);
                }
            }
        }
        while(q--){
            int l,r;
            cin>>l>>r;
            cout<<c[l][r]<<'\n';
        }
        return 0;
    }
    while(q--){
        int l,r,ret=0;
        cin>>l>>r;
        for(int i=1;i<=K;i++){
            ret=max(ret,a[i][r]-a[i][l-1]);
        }
        cout<<ret<<'\n';
    }

    return 0;
}
