#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
constexpr int MN=275,MK=5e4+15;
constexpr ll MOD=2013265921;
ll inv[MN],jc[MN],jcinv[MN],cir[MN],Inv[MN][MN],ans[MK][MN];
ll n,m,k;

ll ksm(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1){
            ret=ret*a%MOD;
        }
        b>>=1;
        a=a*a%MOD;
    }
    return ret;
}

void init(){
    jc[0]=1,inv[1]=1;
    for(int i=1;i<MN;i++){
        jc[i]=jc[i-1]*i%MOD;
        cir[i]=i/2;
    }
    for(int i=2;i<MN;i++){
        inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
    }
    for(int i=MN-1;i>=0;i--){
        jcinv[i]=ksm(jc[i],MOD-2);
    }
    for(int i=1;i<MN;i++){
        Inv[i][0]=1;
        for(int j=1;j<MN;j++){
            Inv[i][j]=Inv[i][j-1]*inv[j]%MOD;
        }
        for(int j=0;j<MN;j++){
            Inv[i][j]=Inv[i][j]*jcinv[j]%MOD;
        }
    }
}

void dfs(ll lst,ll mx,ll bd,ll cnt,ll p){
    if(!lst){
        ans[bd][cnt]+=p;
        return;
    }
    dfs(lst-1,mx,bd,cnt,p);
    for(int i=1;i*lst<=mx;i++){
        for(int j=lst-1;j>=1;j--){
            cir[j]+=__gcd(lst,j);
        }
        dfs(lst-1,mx-i*lst,bd+i*(i-1)/2*lst+cir[lst]*i,cnt+i,p*Inv[lst][i]%MOD);
    }
    if(mx>=lst){
        for(int j=lst-1;j>=1;j--){
            cir[j]-=__gcd(lst,j)*(mx/lst);
        }
    }
}

signed main(){
    // freopen("rgb.in","r",stdin);
    // freopen("rgb.out","w",stdout);
    init();
    cin>>n>>m>>k;
    dfs(n,n,0,0,1);
    ll ret=0;
    for(int i=0;i<=1e4;i++){
        for(int j=0;j<=100;j++){
            if(ans[i][j]){
                ret+=ans[i][j]%MOD*ksm(m,i)%MOD*ksm(k,j)%MOD;
            }
        }
    }
    cout<<ret%MOD;
    return 0;
}