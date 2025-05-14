#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ld long double
using namespace std;
constexpr int MN=1e7+15;
int n;
ll K,T,x[MN],a[MN];

bool check(ll k){
    int l=K,r=K,L,R;
    for(int i=1;i<=n;i++){
        a[i]=(ld)x[i]-(ld)2*k*T*i;
    }
    if(a[1]<a[n]) return 0;
    for(int i=K-1;i>=1;i--){
        if(a[i]>=a[l]) l=i;
    }
    for(int i=K+1;i<=n;i++) if(a[i]<=a[r]) r=i;
    L=K,R=K;
    while(l!=L||r!=R){
        bool flag=0;
        int nl=L,nr=R;
        while(nl>l&&a[nl-1]>=a[R]){
            nl--;
            if(a[nl]>=a[L]) break;
        }
        while(nr<r&&a[nr+1]<=a[L]){
            nr++;
            if(a[nr]<=a[R]) break;
        }
        if(nl<L&&a[nl]>=a[L]){
            L=nl;
            flag=1;
        }
        if(nr>R&&a[nr]<=a[R]){
            R=nr;
            flag=1;
        }
        if(!flag) return 0;
    }
    L=1,R=n;
    while(l!=L||r!=R){
        bool flag=0;
        int nl=L,nr=R;
        while(nl<l&&a[nl+1]>=a[R]){
            nl++;
            if(a[nl]>=a[L]) break;
        }
        while(nr>r&&a[nr-1]<=a[L]){
            nr--;
            if(a[nr]<=a[R]) break;
        }
        if(nl>L&&a[nl]>=a[L]){
            L=nl;
            flag=1;
        }
        if(nr<R&&a[nr]<=a[R]){
            R=nr;
            flag=1;
        }
        if(!flag) return 0;
    }
    return 1;
}

signed main(){
    cin>>n>>K>>T;
    for(int i=1;i<=n;i++) cin>>x[i];
    ll l=0,r=0x3f3f3f3f3f3f;
    while(l+1<r){
        ll mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid;
    }
    cout<<r<<'\n';
    return 0;
}