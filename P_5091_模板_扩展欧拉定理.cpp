#include<iostream>
#define ll long long
using namespace std;
int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while (n%i==0)
            {
                n/=i;
            }
        }
    }
    if(n>=2){
        ans=ans/n*(n-1);
    }
    return ans;
}
inline int read(int mod)
{
	int x=0;
	bool g=false;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^'0');
		if(x>=mod) x%=mod,g=true;//判断是否大于哦啦函数
		c=getchar();
	}
	if(g) return (x+mod);
	else return x;
}
ll quickpow(ll a,ll b,ll mod){
    ll ret=1;
    while (b)
    {
        if (b&1){
            ret=ret*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }
    return ret%mod;
}
int main(){
    ll a,mod,cishu;
    cin>>a>>mod;
    cishu=read(phi(mod));
    cout<<quickpow(a,cishu,mod);
    return 0;
}