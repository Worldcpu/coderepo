#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e8+15,MOD=100000007;
int n;
long long ans=1;
double lgn;
vector<int> prime;
bitset<MN> notp;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void euler(int n){
    notp[1]=1;
    for(int i=2;i<=n;i++){
        if(!notp[i]){
            prime.push_back(i);
            ans=ans*ksm(i,floor(lgn/log(i)))%MOD;
        }
        for(auto p:prime){
            if(p*i>n) break;
            notp[p*i]=1;
            if(i%p==0) break;
        }
    }
    
}


signed main(){
    cin>>n;
    lgn=log(n);
    euler(n);
    cout<<ans;

    return 0;
}