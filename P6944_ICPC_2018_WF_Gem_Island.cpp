#include<bits/stdc++.h>
#define double long double
using namespace std;
constexpr int MN=520+15;
int n,d,r;
double f[MN][MN],g[MN][MN],C[MN][MN];


int main(){
    cin>>n>>d>>r;
    C[0][0]=1;
    for(int i=1;i<=n;i++){
        f[i][0]=C[i][0]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            C[i][j]=C[i-1][j]+C[i-1][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=d;j++){
            for(int k=0;k<=min(i,j);k++){
                f[i][j]+=C[i][k]*f[k][j-k];
            }
        }
    }   
    for(int i=1;i<=n;i++){
        for(int j=1;j<=d;j++){
            for(int k=0;k<=min(i,j);k++){
                g[i][j]+=C[i][k]*(g[k][j-k]+min(k,r)*f[k][j-k]);
            }
        }
    }
    cout<<fixed<<setprecision(8)<<(g[n][d]/f[n][d]+r);
    return 0;
}
