#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int L[MN],R[MN],n;
int pre[MN],suf[MN],K;

bool check(int k){
    for(int i=1,p=1;i<=n;i++){
        while(p<=n&&R[p]<=L[i]+k-1) p++;
        if(suf[i]-1ll*(n-i+1)*L[i]+1ll*(L[i]+k-1)*(p-1)-pre[p-1]<=K) return 1;
    }
    for(int i=n,p=n;i>=1;i--){
        while(p>=1&&L[p]>=R[i]-k+1) p--;
        if(1ll*i*R[i]-pre[i]+suf[p+1]-1ll*(n-p)*(R[i]-k+1)<=K) return 1;
    }
    return 0;
}

#undef int

int plan_vacation(int N,vector<int> a,vector<int> b,long long KK){
    n=N;K=KK;
    ll mn=1e18;
    for(int i=1;i<=n;i++) L[i]=a[i-1],R[i]=b[i-1],mn=min(mn,R[i]-L[i]+1);
    sort(L+1,L+1+n); sort(R+1,R+1+n);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+R[i];
    for(int i=n;i>=1;i--) suf[i]=suf[i+1]+L[i];
    ll l=1,r=mn,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
