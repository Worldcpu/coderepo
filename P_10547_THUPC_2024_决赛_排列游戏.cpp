#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,QM=80,MM=5200,MOD=1e9+7;
int T,n,m,now,inv2=(MOD+1)/2,f[2][MN][MM],ans[MN][MM],pw[MM],inv[MM];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MM;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MM-1]=ksm(pw[MM-1],MOD-2);
    for(int i=MM-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int getpw(int x){
    if(x&1) return MOD-1;
    else return 1;
}

void dodp(){
    initpw();
    f[now][0][0]=1;
    for(int i=1;i<MN;i++){
        now^=1;
        for(int j=0;j<=min(i,QM);j++){
            for(int k=(j-1)*j;k<MM;k+=2){
                f[now][j][k]=0;
                if(j>0) f[now][j][k]=(f[now^1][j-1][k-2*(j-1)]+f[now][j][k]+MOD)%MOD;
                if(k>=2*j) f[now][j][k]=(f[now][j][k]+f[now^1][j][k-2*j]*(2*j+1)+MOD)%MOD;
                if(k>=2*(j+1)) f[now][j][k]=(f[now][j][k]+f[now^1][j+1][k-2*(j+1)]*(j+1)%MOD*(j+1)%MOD)%MOD;
            }
        }
        for(int j=0;j<MM;j++){
            if(j&1) continue;
            int k=j/2,ret=f[now][0][j];
            if(k<=i){
                (ret+=(getpw((i&1)+(k&1))*getC(i-1,k)))%=MOD;
            }
            ret=ret*inv2%MOD;
            ans[i][j]=((j>0?ans[i][j-2]:0)+ret)%MOD;
        }
    }
}


signed main(){
    dodp();
    cin>>T;
    while(T--){
        cin>>n>>m;
        cout<<ans[n][m*2]<<'\n';
    }
    return 0;
}
