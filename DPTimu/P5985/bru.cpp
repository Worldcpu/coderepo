#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=205;
int n,m,a[N],f[64][N][N][2];

main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
    memset(f,-0x3f,sizeof(f));
    for(int i=1;i<=n;i++) f[0][i][i][0]=f[0][i][i][1]=0;
    for(int i=0;i<64;i++) for(int j=1;j<=n+1;j++) for(int k=0;k<2;k++) f[i][j][j-1][k]=0;
    for(int i=1;i<64;i++)
        for(int l=1;l<=n;l++)
            for(int r=l;r<=n;r++)
                for(int j=0;j<2;j++)
                    if(!(m&(1ll<<i-1))&&j) f[i][l][r][j]=f[i-1][l][r][j];
                    else for(int k=l-1;k<=r;k++) f[i][l][r][j]=max(f[i][l][r][j],f[i-1][l][k][0]+f[i-1][k+1][r][j]+a[r]-a[k]);
    cout<<f[63][1][n][1];
}
