#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=10007;
int a,b,k,n,m;


int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int jc(int x){
    int ret=1;
    while(x){
        ret=ret*x%MOD;
        x--;
    }
    return ret;
}

int getc(int x,int y){
    return jc(x)*ksm(jc(y)*jc(x-y),MOD-2)%MOD;
}

signed main(){
    cin>>a>>b>>k>>n>>m;
    cout<<getc(k,n)*ksm(a,n)%MOD*ksm(b,m)%MOD;
    return 0;  
}
