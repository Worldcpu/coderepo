#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr ll prime[]={2,3,5,7,11,13,17,37};

ll qmul(ll a,ll b,ll MOD){
    ll ret=0;
    while(b){
        if(b&1) ret=(ret+a)%MOD;
        b>>=1;
        a=(a+a)%MOD;
    }
    return ret;
}

ll qpow(ll a,ll b,ll MOD){
    ll ret=1;
    while(b){
        if(b&1) ret=qmul(ret,a,MOD);
        a=qmul(a,a,MOD);
        b>>=1;
    }
    return ret;
}

bool MillerRabin(ll n){
    if(n<3||n%2==0) return n==2;
    ll d=n-1,tot=0;
    while(d%2==0) d/=2,++tot;
    for(auto p:prime){
        ll v=qpow(p,d,n);
        if(v==1||v==n-1||v==0) continue;
        for(int j=1;j<=tot;j++){
            v=qmul(v,v,n);
            if(v==n-1&&j!=tot){
                v=1;
                break;
            }
            if(v==1) return 0;
        }
        if(v!=1) return 0;
    }
    return 1;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        ll n;
        cin>>n;
        cout<<(MillerRabin(n)?"YES\n":"NO\n");
    }
    return 0;
}
