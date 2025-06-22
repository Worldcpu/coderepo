#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=1e9+7;
int T,n,m,mu[MN],f[MN],prd[MN];
bool vis[MN];
vector<int> prime;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void euler(int n){
    vis[1]=1;
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime.push_back(i);
            mu[i]=-1;
        }
        for(auto p:prime){
            if(i*p>n) break;
            vis[p*i]=1;
            if(i%p==0){
                mu[i*p]=0;
                break;
            }
            mu[i*p]=-mu[i];
        }
    }
}

void init(){
    euler(MN-1);
    f[1]=f[2]=1;
    for(int i=3;i<MN;i++) f[i]=(f[i-1]+f[i-2])%MOD;
    for(int i=0;i<MN;i++) prd[i]=1;
    for(int i=1;i<MN;i++){
        int inv=ksm(f[i],MOD-2);
        for(int j=i;j<MN;j+=i){
            if(mu[j/i]==-1){
                prd[j]=prd[j]*inv%MOD;
            }else if(mu[j/i]==1) prd[j]=prd[j]*f[i]%MOD;
        }
    }
    for(int i=1;i<MN;i++) prd[i]=prd[i]*prd[i-1]%MOD;
}

void solve(){
    cin>>n>>m;
    int lim=min(n,m);
    int ret=1;
    for(int l=1,r;l<=lim;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ret=ret*ksm(prd[r]*ksm(prd[l-1],MOD-2)%MOD,(n/l)*(m/l))%MOD;
    }
    cout<<ret<<'\n';
}

signed main(){
    init();
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
