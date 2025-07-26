#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=520+15,MM=5e5+15;
int pw[MM],inv[MM],t[MN][MN],C[MN][MN],f[MN][MN],s[MN][MN],g[MN][MN],n,MOD;

ll ksm(ll a,int b){
    ll ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    if(a<MN&&b<MN) return C[a][b];
    return 1ll*pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MM;i++){
        pw[i]=1ll*pw[i-1]*i%MOD;
    }
    inv[MM-1]=ksm(pw[MM-1],MOD-2);
    for(int i=MM-2;i>=0;i--){
        inv[i]=1ll*inv[i+1]*(i+1)%MOD;
    }
    for(int i=0;i<MN;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
        }
    }
}

signed main(){
    cin>>n>>MOD;
    initpw();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            t[i][j]=getC(n+i*j-1,i*j-1);
        }
    }
    for(int j=1;j<=n;j++){
        for(int a=1;a<=n;a++){
            for(int b=1;b<=j;b++){
                int ret=1ll*getC(j,b)*t[a][b]%MOD;
                if((j-b)&1) s[j][a]=(s[j][a]-ret+MOD)%MOD;
                else s[j][a]=(s[j][a]+ret)%MOD;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int a=1;a<=i;a++){
                int ret=1ll*getC(i,a)*s[j][a]%MOD;
                if((i-a)&1) g[i][j]=(g[i][j]-ret+MOD)%MOD;
                else g[i][j]=(g[i][j]+ret)%MOD;
            }
        }
    }
    memset(s,0,sizeof(s));
    for(int j=0;j<n;j++){
        for(int a=0;a<n;a++){
            for(int b=j;b<n;b++){
                int ret=1ll*getC(b,j)*g[n-a][n-b]%MOD;
                if((b-j)&1) s[j][a]=(s[j][a]-ret+MOD)%MOD;
                else s[j][a]=(s[j][a]+ret)%MOD;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int a=i;a<n;a++){
                int ret=1ll*getC(a,i)*s[j][a]%MOD;
                if((a-i)&1) f[i][j]=(f[i][j]-ret+MOD)%MOD;
                else f[i][j]=(f[i][j]+ret)%MOD;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<f[i][j]<<" ";
        }
        cout<<'\n';
    }
    return 0;
}