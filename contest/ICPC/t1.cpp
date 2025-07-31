#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,m,mx,a[MN],b[MN];

bool check(int mid){
    for(int i=1;i<=n;i++){

    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mx=max(mx,a[i]);
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
        mx=max(mx,b[i]);
    }
    int l=1,r=mx*n*m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            l=mid+1,ans=mid;
        }else r=mid-1;
    }
    cout<<ans;

    return 0;
}