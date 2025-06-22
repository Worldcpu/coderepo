#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
constexpr int MN=5e5+15;
vector<bool> vis(MN);
vector<ll> prime;
ll n,m,K,T,mu[MN],sum[MN];

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
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+mu[i];
}

void solve(){
    cin>>n>>m>>K;
    int lim=min(n,m),ans=0;
    for(int l=1,r;l<=lim;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=(n/(l*K))*(m/(l*K))*(sum[r]-sum[l-1]);
    }
    cout<<ans<<'\n';
}

signed main(){
    euler(5e4+15);
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
