#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MS=1<<15,MN=15,INF=1e18;
int f[MS],lim[MS],sum[MS],a[MN],n,m;
vector<int> ans;

int dfs(int S){
    if(!S) return lim[n];
    if(f[S]!=0) return f[S];
    int rt=__builtin_ctzll(S),SS=S^(1<<rt);
    for(int T=SS;;T=(T-1)&SS){
        f[S]=max(f[S],dfs(T)+dfs(SS^T)+a[rt]);
        if(!T) break;
    }
    f[S]=min(f[S],lim[rt]);
    if(sum[S]>=lim[rt]) f[S]=-INF;
    return f[S];
}

signed main(){
    cin>>m>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int S=0;S<(1<<n);S++){
        lim[0]=m+1;
        for(int i=1;i<=n;i++){
            lim[i]=lim[i-1];
            if(~(S>>(i-1))&1) lim[i]=min(lim[i],a[i-1]);
        }
        if(S){
            sum[S]=sum[S^(S&-S)]+a[__builtin_ctzll(S)];
        }
        memset(f,0,sizeof(f));
        if(dfs(S)>=m){
            ans.push_back(sum[S]);
        }
    }
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    cout<<ans.size()<<'\n';
    for(auto p:ans){
        cout<<p<<" ";
    }
    

    return 0;
}