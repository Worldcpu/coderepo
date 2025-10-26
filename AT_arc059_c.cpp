#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=1e9+7;
int n,c,a[MN],b[MN];
int f[MN][MN],w[MN][MN];


void initw(){
    for(int i=1;i<MN;i++) w[i][0]=1ll;
    for(int i=1;i<MN;i++){
        for(int j=1;j<MN;j++){
            w[i][j]=w[i][j-1]*i%MOD;
        }
    }
    for(int i=1;i<MN;i++){
        for(int j=0;j<MN;j++){
            w[i][j]=(w[i][j]+w[i-1][j])%MOD;
        }
    }
}

signed main(){
    cin>>n>>c;
    initw();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    f[0][0]=1ll;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=c;j++){
            for(int k=0;k<=j;k++){
                f[i][j]=(f[i][j]+f[i-1][j-k]*(w[b[i]][k]-w[a[i]-1][k]+MOD)%MOD)%MOD;
            }
        }
    }
    cout<<f[n][c];

    return 0;
}