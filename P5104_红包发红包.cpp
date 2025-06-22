#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=1e9+7;
int w,n,K;

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
    cin>>w>>n>>K;
    cout<<w*ksm(ksm(2,K),MOD-2)%MOD;
    return 0;
}
