#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=520,MOD=998244353,INF=0x3f3f3f3f;
int f[MN][MN],n,m,pw[MN],inv[MN];
int mnr[MN][MN],tmp[MN][MN]; 
vector<pir> vct[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

signed main(){
    initpw();
    cin>>n>>m;  

    for(int i=1;i<=m;i++){
        int l,r,x;
        cin>>l>>r>>x;
        vct[x].push_back(pir(l,r));
    }

    memset(tmp,0x3f,sizeof(tmp));
    for(int x=1;x<=n;x++){
        for(auto [l,r]:vct[x]){
            tmp[x][l]=min(tmp[x][l],r);
        }
        mnr[x][n+1]=INF;
        for(int l=n;l>=1;l--){
            mnr[x][l]=min(tmp[x][l],mnr[x][l+1]);
        }
    }

    for(int i=1;i<=n+1;i++) f[i][i-1]=1;
    for(int len=1;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int k=l;k<=r;k++){
                if(mnr[k][l]<=r) continue;
                f[l][r]=(f[l][r]+f[l][k-1]*f[k+1][r]%MOD*getC(r-l,k-l)%MOD)%MOD;
            }
        }
    }
    cout<<f[1][n]<<"\n";

    return 0;
}
