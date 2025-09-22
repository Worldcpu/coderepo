#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,L,a[MN],b[MN];

bool check(int k){
    int mx=-1e18,l=1,r=1;
    for(int i=1;i<=2*n;i++){
        while(l<=4*n&&b[l]<a[i]-k) l++;
        while(r<=4*n&&b[r]<=a[i]+k) r++;
        mx=max(mx,l-i);
        if(r-i-1<mx) return 0;
    }
    return 1;
}

signed main(){
    cin>>n>>L;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    sort(a+1,a+1+n);
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++){
        a[i]+=L;
        a[i+n]=a[i]+L;
    }
    for(int i=1;i<=3*n;i++){
        b[i+n]=b[i]+L;
    }
    int l=0,r=L>>1,ret=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ret=mid;
        else l=mid+1;
    }
    cout<<ret;
    return 0;
}