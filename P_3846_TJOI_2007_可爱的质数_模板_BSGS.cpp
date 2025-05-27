#include<bits/stdc++.h>
#define int long long
using namespace std;
int p,b,n;
map<int,int> mp;

int qpow(int a,int b,int mod){
    int ret=1;
    while(b){
        if(b&1){
            ret=ret*a%mod;
        }
        b>>=1;
        a=a*a%mod;
    }
    return ret;
}

int BSGS(int a,int b,int p){
    mp.clear();
    b%=p;
    int t=sqrt(p)+1;
    for(int j=0;j<t;j++){
        int val=b*qpow(a,j,p)%p; //b*a^j
        mp[val]=j;
    }
    a=qpow(a,t,p);
    if(a==0) return b==0?1:-1;
    for(int i=0;i<t;i++){
        int val=qpow(a,i,p); //(a^t)^i
        int j=mp.find(val)==mp.end()?-1:mp[val];
        if(j>=0&&i*t-j>=0) return i*t-j;
    }
    return -1;
}

signed main(){
    cin>>p>>b>>n;
    int ret=BSGS(b,n,p);
    if(ret==-1) cout<<"no solution";
    else cout<<ret;
    return 0;
}
