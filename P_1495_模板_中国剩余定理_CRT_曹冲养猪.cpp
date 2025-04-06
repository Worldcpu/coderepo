#include<iostream>
#define ll long long
using namespace std;
const int MN=1e5+15;
int a[MN],b[MN],n;
ll mt=1;
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
ll inv(ll a,ll n){
    ll x,y;
    exgcd(a,n,x,y);
    return (x%n+n)%n;
}
long long quick_mul(long long x,long long y,long long mod) 
{
	long long ans=0;
	while(y!=0){
		if(y&1==1)ans+=x,ans%=mod;
		x=x+x,x%=mod;
		y>>=1; 
	}
	return ans;
}
ll crt(){
    ll ans=0;
    for(int i=1;i<=n;i++){
        ll m=mt/a[i],invm=inv(m,a[i]);
        ll ci=m*invm;
        ans=(ans+quick_mul(b[i],ci,mt))%mt;
    }
    return (ans%mt+mt)%mt;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        mt*=a[i];
    }
    cout<<crt();
    return 0;
}