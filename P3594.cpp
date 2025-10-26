#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,p,d,q[MN],ql,qr,sum[MN],a[MN],ans;


signed main(){
    cin>>n>>p>>d;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    ans=d;
    ql=1;
    q[++qr]=d;
    for(int i=d+1,l=1;i<=n;i++){
        while(ql<=qr&&sum[i]-sum[i-d]>sum[q[qr]]-sum[q[qr]-d]) qr--;
        q[++qr]=i;
        while(ql<=qr&&sum[i]-sum[l-1]-sum[q[ql]]+sum[q[ql]-d]>p){
            l++;
            while(ql<=qr&&q[ql]-d+1<l) ql++;
        }
        ans=max(ans,i-l+1);
    }
    cout<<ans;

    return 0;
}