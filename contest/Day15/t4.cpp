#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
constexpr int MN=1e7+15,MOD=1e9+7;
vector<bool> vis(MN);
vector<ll> prime;
ll n,m,ans,mu[MN];

void euler(int n){
    vis[1]=1;
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime.push_back(i);
            mu[i]=MOD-1;
        }
        for(auto p:prime){
            if(i*p>n) break;
            vis[p*i]=1;
            if(i%p==0){
                mu[i*p]=0;
                break;
            }
            mu[i*p]=MOD-mu[i];
        }
    }
}

int sum(int n){
    int ret=0;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        ret=(ret+(r-l+1)*(n/l)%MOD)%MOD;
    }
    return ret;
}

signed main(){
    cin>>n;
    m=sqrt(n)+1;
    euler(m);
    for(int i=1;i<=m;i++){
        ans=(ans+mu[i]*sum(n/(i*i))%MOD)%MOD;
    }
    cout<<ans;

    return 0;
}