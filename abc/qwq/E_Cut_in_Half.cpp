#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e5+5;
int n,K,X; ll a[MN];
inline ll read(){
    ll x=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline bool check(long double k){
    ll c=0,s=0;
    for(int i=1;i<=n;i++){
        if(a[i]<k) break;
        c++;
        ll v=a[i]/k;
        if(v>0){
            ll t=63-__builtin_clzll(v);
            s+=1ll<<t;
            if(s>=1000000000000000000LL) return true;
        }
    }
    ll u=s-c;
    ll ret = (K<=u)? c+K : max(0ll,s-(K-u));
    return ret>=X;
}
void solve(){
    n=read();K=read();X=read();
    for(int i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+n+1,greater<ll>());
    long double l=0,r=a[1],ans=0;
    for(int i=0;i<70;i++){
        long double m=(l+r)/2;
        if(check(m)) ans=m,l=m;
        else r=m;
    }
    printf("%.9Lf\n",ans);
}
int main(){
    int T=read();
    while(T--) solve();
}
