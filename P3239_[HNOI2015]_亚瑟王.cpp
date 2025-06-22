#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520+15;
constexpr double eps=1e-10;
int d[MN],n,r,T;
double f[MN][MN],pw[MN][MN],fp[MN],p[MN],ans;

void initpw(){
    for(int i=1;i<=n;i++){
        pw[i][0]=1;
        for(int j=1;j<=r;j++){
            pw[i][j]=pw[i][j-1]*(1-p[i]);
        }
    }
}

void solve(){
    memset(f,0,sizeof(f));
    memset(fp,0,sizeof(fp));
    cin>>n>>r;
    for(int i=1;i<=n;i++){
        cin>>p[i]>>d[i];
    }
    initpw();
    f[1][0]=pw[1][r],f[1][1]=fp[1]=1-f[1][0];
    for(int i=2;i<=n;i++){
        for(int j=0;j<=r;j++){
            fp[i]+=f[i-1][j]*(1-pw[i][r-j]);
            f[i][j]+=f[i-1][j]*pw[i][r-j];
            if(j) f[i][j]+=f[i-1][j-1]*(1-pw[i][r-j+1]);
        }
    }
    ans=0;
    for(int i=1;i<=n;i++) ans+=d[i]*fp[i];
    cout<<fixed<<setprecision(10)<<ans<<'\n';
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
