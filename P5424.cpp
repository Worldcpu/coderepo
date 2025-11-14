#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int f[MN][MN],n,a[MN],g[MN][MN],K;


signed main(){
    cin>>n>>K;
    K++;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        int sum=0,mx=0;
        for(int j=i;j<=n;j++){
            mx=max(mx,a[j]);
            sum+=a[j];
            g[i][j]=mx*(j-i+1)-sum;
        }
    }
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int k=1;k<=K;k++){
        for(int i=1;i<=n;i++){
            for(int j=0;j<i;j++){
                f[i][k]=min(f[i][k],f[j][k-1]+g[j+1][i]);
            }
        }
    }
    cout<<f[n][K];
    return 0;
}