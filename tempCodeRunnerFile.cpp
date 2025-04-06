#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e6+15;
ll P,n,fsum[MN],pphi[MN],inv4,inv6;
vector<bool> vis(MN);
vector<int> prm;
unordered_map<int,ll> ump;

void getphi(int k){
    pphi[1]=1;
    for(int i=2;i<=k;i++){
        if(!vis[i]){
            prm.push_back(i);
            pphi[i]=i-1;
        }
        for(auto p:prm){
            if(i*p>k) break;
            vis[i*p]=1;
            if(!(i%p)){
                pphi[i*p]=pphi[i]*p;
                break;
            }
            else pphi[i*p]=pphi[i]*(p-1);
        }
    }
}

// ll getfg(ll r){
//     return ((r*(r+1)/2)%P*(r*(r+1)/2)%P)%P;
// }

ll getlfsum(ll k){
    k%=P;
    return k*(k+1)%P*k*(k+1)%P*inv4%P;
}

long long getpfsum(long long k) {  // 平方和
    return k %= P, k * (k + 1) % P * (k * 2 + 1) % P * inv6 % P;
  }

ll dushu(ll k){
    if(k<MN) return fsum[k];
    if(ump[k]) return ump[k];
    ll ans=getlfsum(k),pre=1,now;
    for(int i=2,j;i<=k;i=j+1){
        j=k/(k/i);
        now=getpfsum(j);
        ans=(ans-(now-pre)*dushu(k/i)%P)%P;
        pre=now;
    }
    return ump[k]=(ans+P)%P;
}

void getsum(){
    for(ll i=1;i<MN;i++){
        fsum[i]=(fsum[i-1]+i*i%P*pphi[i]%P)%P;
    }
}

ll ksm(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%P;
        }
        a=a*a%P;
        b>>=1;
    }
    return ans;
}

ll g(ll a,ll b){
    return a*(a-1)%P*b*(b-1)%P*inv4%P;
}

ll solve(){
    ll ans=0,pre=0,now;
    for(ll i=1,j;i<=n;i=j+1){
        j=n/(n/i);
        now=dushu(j);
        ans=(ans+(now-pre)*getlfsum(n/i)%P)%P;
        pre=now;
    }
    return (ans+P)%P;
}

int main(){
    cin>>P>>n;
    getphi(n);
    // for(int i=1;i<=10;i++) cout<<pphi[i]<<" ";
    getsum();
    inv4=ksm(4,P-2);
    inv6=ksm(6,P-2);
    cout<<solve();
    return 0;
}