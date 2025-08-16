#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=220,MOD=998244353,N=105;
int n,f[MN],g[MN][MN][MN],h[MN][MN][MN],pw[MN],w1,w2,w3,w4,ans1,ans2;

void initpw(){
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*(w1+w2+w3+w4)%MOD;
}

signed main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>n>>w1>>w2>>w3>>w4;
    initpw();
    g[0][0+N][0+N]=1;
    for(int t=1;t<=n;t++)
        for(int x=-t;x<=t;x++)
            for(int y=-t;y<=t;y++){
                int tmp=g[t-1][x+N][y+N];
                (g[t][x+1+N][y+N]+=tmp*w1)%=MOD;
                (g[t][x-1+N][y+N]+=tmp*w2)%=MOD;
                (g[t][x+N][y+1+N]+=tmp*w3)%=MOD;
                (g[t][x+N][y-1+N]+=tmp*w4)%=MOD;
            }

    for(int i=0;i<=n;i++){
        f[i]=pw[i];
        for(int j=0;j<i;j++) f[i]=(f[i]-f[j]*g[i-j][0+N][0+N]%MOD+MOD)%MOD;
        ans1=(ans1+f[i]*pw[n-i]%MOD)%MOD;
    }

    for(int i=1;i<=n;i++)
        for(int x=-i;x<=i;x++)
            for(int y=-i;y<=i;y++){
                if(x==0 && y==0) continue;
                int &r=h[i][x+N][y+N];
                for(int j=0;j<i;j++){
                    (r+=f[j]*g[i-j][x+N][y+N]%MOD)%=MOD;
                    (r+=(MOD-h[j][-x+N][-y+N]*g[i-j][x+N][y+N]%MOD)%MOD)%=MOD;
                    (r+=(MOD-h[j][x+N][y+N]*g[i-j][0+N][0+N]%MOD)%MOD)%=MOD;
                }
                ans2=(ans2+r*pw[n-i]%MOD)%MOD;
            }

    ans2=(ans1+ans2+ans2)%MOD;
    cout<<((ans2*pw[n]%MOD-ans1*ans1%MOD+MOD)%MOD);
}
