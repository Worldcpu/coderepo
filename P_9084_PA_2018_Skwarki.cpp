#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MN=1520;
int f[MN][MN][2],pw[MN],inv[MN],n,K,nj,MOD;

template<typename type>
inline type read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return flag?x=-x:x;
}

template<typename type>
inline void write(type x)
{
    x<0?x=-x,putchar('-'):0;
    static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10;while(x);
    while(top) putchar(Stack[top--]|48);
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    read(n),read(K),read(MOD);
    if(K>__lg(n)+1){
        cout<<0;
        return 0;
    }
    init();
    f[0][0][0]=f[0][0][1]=1;
    for(int i=1;i<n;i++){
        for(int j=1;j<=i;j++){
            for(int l=0;l<=K;l++){
                for(int r=0;r<=K;r++){
                    nj=(l==r)?l+1:max(l,r);
                    f[i][nj][0]=(f[i][nj][0]+f[j-1][l][0]*f[i-j][r][0]*getC(i-1,j-1)%MOD)%MOD;
                    nj=max(l,r+1);
                    f[i][nj][1]=(f[i][nj][1]+f[j-1][l][1]*f[i-j][r][0]%MOD*getC(i-1,j-1)%MOD)%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int l=0;l<=K;l++){
            for(int r=0;r<=K;r++){
                if(max(l,r)==K){
                    ans=(ans+(f[i-1][l][1]*f[n-i][r][1]%MOD*getC(n-1,i-1)%MOD))%MOD;
                }
            }
        }
    }
    write(ans);
    return 0;
}
