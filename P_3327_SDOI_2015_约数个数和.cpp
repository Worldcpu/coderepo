#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,mu[MN],sum[MN];
vector<bool> vis(MN);
vector<int> prime;

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
    for(int i=1;i<=n;i++) mu[i]+=mu[i-1];
    for(int i=1;i<=n;i++){
        int ret=0;
        for(int l=1,r;l<=i;l=r+1){
            r=(i/(i/l));
            ret+=(r-l+1)*(i/l);
        }
        sum[i]=ret;
    }
}

void solve(){
    int n,m;
    cin>>n>>m;
    long long ret=0;
    for(int l=1,r;l<=min(n,m);l=r+1){
        r=min(n/(n/l),m/(m/l));
        ret+=1ll*(mu[r]-mu[l-1])*sum[n/l]*sum[m/l];
    }
    cout<<ret<<'\n';
}

signed main(){
    euler(5e4+15);
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}