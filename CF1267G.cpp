#include<bits/stdc++.h>
#define double long double
using namespace std;
constexpr int MN=122,MV=1e4+15;
int n,m,x,c[MN];
double f[MN][MV],ans;

int main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        m+=c[i];
    }
    f[0][0]=1.0;
    for(int i=1;i<=n;i++){
        for(int j=i;j>=1;j--){
            for(int k=c[i];k<=m;k++){
                f[j][k]+=f[j-1][k-c[i]]*1.0*j/(n-j+1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            ans+=f[i][j]*min(1.0*j/i,(1.0*n/i+1)*x/2);
        }
    }
    cout<<fixed<<setprecision(10)<<ans;
    return 0;
}