#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=22,MP=1e5+15,MS=(1<<21),MOD=998244353;
int f[2][MN][MS],a[MN],n,m,ans,tmp[MN];

namespace Calcpw{
    int pw[MP],inv[MP];

    int ksm(int a,int b){
        int ret=1;
        while(b){
            if(b&1) ret=1LL*ret*a%MOD;
            a=1LL*a*a%MOD;
            b>>=1;
        }
        return ret;
    }

    void initpw(){
        pw[0]=1;
        for(int i=1;i<MP;i++){
            pw[i]=1LL*pw[i-1]*i%MOD;
        }
        inv[MP-1]=ksm(pw[MP-1],MOD-2);
        for(int i=MP-2;i>=0;i--) inv[i]=1LL*inv[i+1]*(i+1)%MOD;
    }

    int getC(int a,int b){
        if(a<b||a<0||b<0) return 0;
        return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
    }
}using Calcpw::getC;

namespace Calcst{
    int rk[MN];

    int calcst(int n,int st[]){
        int now=0,ret=0;
        for(int i=1;i<=n;i++){
            if(st[i]>now){
                ret|=(1<<(i-1));
                now=st[i];
            }
        } 
        return ret;
    }

    void getst(int n,int st,int res[]){
        res[0]=0;
        for(int i=1;i<=n;i++){
            res[i]=res[i-1]+((st>>(i-1))&1); 
        }
    }
}using namespace Calcst;

signed main(){
    Calcpw::initpw();
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];

    f[0][0][0]=1;
    for(int i=0;i<n;i++){
        int now=i&1,nxt=now^1;
        for(int j=0;j<=i+1;j++) {
            for(int s=0;s<(1<<j);s++) f[nxt][j][s]=0;
        }
        for(int j=0;j<=i;j++){ 
            for(int s=0;s<(1<<j);s++){
                getst(j,s,rk);
                for(int k=1;k<=j;k++){
                    if(rk[k-1]==a[i+1]-1){
                        int tmp=rk[k];
                        rk[k]=a[i+1];
                        int st=calcst(j,rk);  
                        f[nxt][j][st]=(f[nxt][j][st]+f[now][j][s])%MOD;
                        rk[k]=tmp;
                    }
                }

                memcpy(tmp,rk,sizeof(rk));
                for(int k=0;k<=j;k++){
                    if(rk[k]!=a[i+1]-1) continue;

                    for(int p=j+1;p>k+1;p--) rk[p]=rk[p-1];
                    rk[k+1]=a[i+1];

                    int st=calcst(j+1,rk); 
                    f[nxt][j+1][st]=(f[nxt][j+1][st]+f[now][j][s])%MOD;

                    memcpy(rk,tmp,sizeof(tmp));
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int s=0;s<(1<<i);s++){
            ans=(ans+1LL*getC(m,i)*f[n&1][i][s]%MOD)%MOD;
        }
    }

    cout<<ans;
    return 0;
}
