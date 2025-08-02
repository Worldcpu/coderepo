#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e7+15,MM=5e5+15,MOD=1e9+7;
vector<bool> vis(MN);
vector<int> prime;
int n,mxv,mu[MN],pw[MM],cnt[MN],f[MN],g[MN];
long long ans,s[MN];

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

void initpw(){
    pw[0]=1;
    for(int i=1;i<MM;i++){
        pw[i]=pw[i-1]*2%MOD;
    }
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        cnt[x]++;
        mxv=max(mxv,x);
    }
    euler(mxv);
    for(auto p:prime){
        for(int i=mxv/p;i>=1;i--){
            cnt[i]+=cnt[i*p];
        }
    }
    for(int i=1;i<=mxv;i++){
        g[i]=mu[i]*cnt[i];
    }
    for(auto p:prime){
        for(int i=1;i*p<=mxv;i++){
            g[i*p]+=g[i];
        }
    }
    reverse(prime.begin(),prime.end());
    for(int i=1;i<=mxv;i++){
        s[i]=pw[cnt[i]]-1;
    }
    for(auto p:prime){
        for(int i=1;i*p<=mxv;i++){
            s[i]=(s[i]-s[i*p]+MOD)%MOD;
        }
    }
    for(int i=mxv;i>1;i--){
        ans=(ans+s[i]*g[i]%MOD)%MOD;
    }
    cout<<ans;

    return 0;
}