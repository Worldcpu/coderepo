#include<iostream>
#define ll long long
using namespace std;
const int MN=10;
int k;
ll a[MN],b[MN],mb=1;
ll slowtime(ll a,ll b,ll mod){
    ll ret=0;
    while (b>0)
    {
        if(b&1) ret=(ret+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return ret;
}
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    ll ret=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return ret;
}
ll inv(ll a,ll n){
    ll x,y;
    exgcd(a,n,x,y);
    return (x%n+n)%n;
}
ll crt(){
    ll ans=0;
    for(int i=1;i<=k;i++){
        ll m=mb/b[i],mi=inv(m,b[i]);
        ll c=m*mi;
        ans=(ans+slowtime(a[i],c,mb))%mb;
    }
    return ans;
}
int main(){
    cin>>k;
    for(int i=1;i<=k;i++){
        cin>>a[i];
    }
    for(int i=1;i<=k;i++){
        cin>>b[i];
        mb*=b[i];
    }
    cout<<crt();
    return 0;
}