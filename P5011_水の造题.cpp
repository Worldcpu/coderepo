#include<bits/stdc++.h>
#include <cmath>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=19491001;
int n,K,sum;

template<typename type>
inline type read(type &x,int MOD=LONG_LONG_MAX)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
    while(isdigit(ch)) x=((x<<1)+(x<<3)+(ch^48))%MOD,ch=getchar();
    return flag?x=-x:x;
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int inv(int x){
    return ksm(x,MOD-2);
}

signed main(){
    read(n,MOD);
    read(K);
    for(int i=1;i<=K;i++){
        int x;
        read(x);
        sum=(sum+x)%MOD;
    }
    int t=(n-1+MOD)*inv(K*K%MOD)%MOD,invk=inv(K);
    cout<<((sum*t%MOD*2%MOD)+invk*n%MOD*sum)%MOD;
    return 0;
}
