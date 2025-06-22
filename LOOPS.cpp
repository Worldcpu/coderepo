#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
constexpr int MN=1520;
constexpr double eps=1e-5;
int n,m;
double f[MN][MN],a[MN][MN],b[MN][MN],c[MN][MN];



void solve(){
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=m+1;j++){
            f[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j]>>b[i][j]>>c[i][j];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
            if(1.0-a[i][j]<eps) continue;
            f[i][j]=(b[i][j]*f[i][j+1]+c[i][j]*f[i+1][j]+2.0)/(1-a[i][j]);
        }
    }
    cout<<fixed<<setprecision(3)<<f[1][1]<<'\n';
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin>>n>>m){
        solve();
    }
}

