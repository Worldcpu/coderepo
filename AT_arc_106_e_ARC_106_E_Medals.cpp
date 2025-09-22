#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e6+15;
int st[MN],f[MN],a[MN],n,K,lim;

bool check(int k){
    for(int i=0;i<(1<<n);i++) f[i]=0;
    for(int i=1;i<=k;i++){
        f[st[i]]++;
    }
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++){
            if(!(s>>i&1)){
                f[s|(1<<i)]+=f[s];
            }
        }
    }
    for(int i=0;i<(1<<n);i++){
        if(k-f[(1<<n)-i-1]<__builtin_popcount(i)*K) return 0;
    }
    return 1;
}

signed main(){
    cin>>n>>K;
    lim=2*n*K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=lim;i++){
        for(int j=1;j<=n;j++){
            if((i+a[j]-1)/a[j]%2!=0) st[i]|=(1<<j-1);
        }
    }
    int l=1,r=lim;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    cout<<l;

    return 0;
}