#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=100003;
int n,m;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>m>>n;
    cout<<(ksm(m,n)-ksm(m-1,n-1)*m%MOD+MOD)%MOD;
    return 0;
}
