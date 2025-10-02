#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=(1<<17)+5,INF=1e18;
int a[MN],n,m,K,id[MN],f[MN];
vector<int> ans;

int check(int pos,int k){
    if((pos<<1)>=n){
        f[pos]=(a[pos<<1]<k?INF:(a[pos<<1|1]<k?a[pos]:0));
    }else{
        check(pos<<1,k);
        check(pos<<1|1,k);
        f[pos]=min(INF,f[pos<<1]+min(a[pos],f[pos<<1|1]));
    }
    return f[pos];
}

void dfs(int u){
    int l=1,r=n,ret=l;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(u,mid)<=K) l=mid+1,ret=mid;
        else r=mid-1;
    }
    check(u,ret);
    ret=id[ret];
    K-=f[u];
    ans.push_back(a[ret]);
    ans.push_back(a[ret^1]);
    for(int i=ret>>1;i!=u;i>>=1){
        if(i&1) K+=f[i^1];
        else if(f[i^1]<=a[i>>1]) K+=f[i^1];
        else if(K>=f[i^1]-a[i>>1]) K+=a[i>>1];
        dfs(i^1);
    }
}

void init(){
    ans.clear();
}

void solve(){
    cin>>m>>K;
    init();
    n=1<<m;
    for(int i=1;i<2*n;i++){
        cin>>a[i];
    }
    for(int i=n;i<2*n;i++){
        id[a[i]]=i;
    }
    dfs(1);
    for(auto p:ans) cout<<p<<' ';
    cout<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}