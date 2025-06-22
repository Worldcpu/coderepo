#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e3+15;
double f[MN][MN],p;
int n,T;

int main(){
    cin>>n>>p>>T;
    f[0][0]=1;
    for(int i=1;i<=T;i++){
        f[i][0]=f[i-1][0]*(1.0-p);
        for(int j=1;j<=min(i,n);j++){
            if(j==n){
                f[i][j]=f[i-1][j]+p*f[i-1][j-1];
            }else f[i][j]=f[i-1][j]*(1.0-p)+p*f[i-1][j-1];
        }
    }
    double ans=0.0;
    for(int i=1;i<=n;i++){
        ans+=f[T][i]*i;
    }
    cout<<fixed<<setprecision(7)<<ans;
    return 0;
}
