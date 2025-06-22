#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int q,n;
double f[MN],g[MN][MN];

void solve1(){
    for(int i=2;i<=n;i++){
        f[i]=f[i-1]+2.0/i;
    }
    cout<<fixed<<setprecision(6)<<f[n]<<'\n';
}

void solve2(){
    for(int i=1;i<=n;i++){
        g[i][0]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            for(int k=1;k<i;k++){
                g[i][j]+=(g[k][j-1]+g[i-k][j-1]-g[k][j-1]*g[i-k][j-1]);
            }
            g[i][j]/=(i-1);
        }
    }
    double ans=0;
    for(int i=1;i<n;i++){
        ans+=g[n][i];
    }
    cout<<fixed<<setprecision(6)<<ans;
}

int main(){
    cin>>q>>n;
    if(q==1){
        solve1();
    }else solve2();


    return 0;
}
