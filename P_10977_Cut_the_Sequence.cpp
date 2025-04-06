#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=1e5+15;
multiset<ll> s;
ll a[MN],q[MN],f[MN],sum[MN];
int n,m,ql,qr;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]>m){
            cout<<-1;
            return 0;
        }
        sum[i]=sum[i-1]+a[i];
    }
    ql=1,qr=0;
    for(int i=1;i<=n;i++){
        while(ql<=qr&&sum[i]-sum[q[ql]]>m){//去大于m的决策
            s.erase(f[q[ql]]+a[q[ql+1]]);
            ql++;
        }
        while(ql<=qr&&a[q[qr]]<a[i]){//A[j]单调递减
            s.erase(f[q[qr-1]]+a[q[qr]]);
            qr--;
        }
        if(ql<=qr){
            s.insert(f[q[qr]]+a[i]);
        }
        q[++qr]=i;
        int l=0,r=i-1,ret;
        while (l<=r)
        {
            int mid=l+r>>1;
            if(sum[i]-sum[mid]<=m){
                r=mid-1;
                ret=mid;
            }else l=mid+1;
        }
        f[i]=f[ret]+a[q[ql]];
        if(s.size()){
            f[i]=min(f[i],*s.begin());
        }
    }
    cout<<f[n];
    return 0;
}