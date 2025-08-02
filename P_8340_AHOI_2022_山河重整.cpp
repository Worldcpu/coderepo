#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e5+15;
int lim,f[MN],g[MN],pw2[MN],n,MOD;
ll ans;

inline void add(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
inline void sub(int &x,int y){x-=y;if(x<0)x+=MOD;}
inline int mul(int x,int y){return 1ll*x*y%MOD;}

void solve(int x){
    if(x<=1)return;
    solve(x>>1);
    for(int i=0;i<=x;i++)g[i]=0;
    lim=sqrt(2*x);
    for(int i=lim;i>=1;i--){
        for(int j=x;j>=i;j--)g[j]=g[j-i];
        for(int j=0;j<i;j++)g[j]=0;
        for(int j=0;j+(j+2)*i<=x;j++)add(g[j+(j+2)*i],f[j]);
        for(int j=i;j<=x;j++)add(g[j],g[j-i]);
    }
    for(int i=(x>>1)+1;i<=x;i++)sub(f[i],g[i]);
}

void initpw(){
    pw2[0]=1;
    for(int i=1;i<MN;i++)pw2[i]=mul(pw2[i-1],2);
}

signed main(){
    cin>>n>>MOD;
    initpw();
    lim=sqrt(2*n);
    f[0]=1;
    for(int i=lim;i>=1;i--){
        for(int j=n;j>i;j--)f[j]=f[j-i];
        for(int j=1;j<=i;j++)f[j]=0;
        for(int j=i;j<=n;j++)add(f[j],f[j-i]);
    }
    solve(n);
    for(int i=0;i<n;i++)ans=(ans+mul(f[i],pw2[n-i-1]))%MOD;
    ans=(pw2[n]-ans+MOD)%MOD;
    cout<<ans;
    return 0;
}
