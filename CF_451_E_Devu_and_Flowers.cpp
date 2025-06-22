#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15,MOD=1e9+7;
int n,f[MN],m,ans,inv[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    inv[1]=1;
    for(int i=2;i<MN;i++) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
}

int C(int n,int r) {
	if (n<r) return 0;
	r=min(r,n-r);
	int res=1,a=1,b=1;
	for (int i=1;i<=r;i++)
		a=a*(n-i+1)%MOD,b=b*i%MOD;
	res=res*a%MOD*ksm(b,MOD-2)%MOD;
	return res;
}

int lucas(int n,int m){
    if(n<m) return 0;
    if(!n) return 1;
    return lucas(n/MOD,m/MOD)*C(n%MOD,m%MOD)%MOD;
}

signed main(){
    init();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>f[i];
    }
    for(int s=0;s<1<<n;s++){
        if(!s){
            (ans+=lucas(n+m-1,n-1))%=MOD;
            continue;
        }else{
            int t=n+m-1;
            for(int i=0;i<n;i++){
                if((s>>i)&1){
                    t-=f[i+1];
                }
            }
            t-=__builtin_popcountll(s);
            if(t<0) continue;
            if(__builtin_popcountll(s)&1) ans=(ans-lucas(t,n-1)+MOD)%MOD;
            else ans=(ans+lucas(t,n-1))%MOD;
        }
    }
    cout<<ans;
    return 0;
}
