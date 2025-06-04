#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,P=999911658;
int n,g,fc[MN],a[MN],b[MN]={0,2,3,4679,35617};

int ksm(int a,int b,int MOD){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(int p){
    fc[0]=1;
    for(int i=1;i<=p;i++){
        fc[i]=fc[i-1]*i%p;
    }
}

int getC(int a,int b,int MOD){
    if(a<b) return 0;
    return fc[a]*ksm(fc[b],MOD-2,MOD)%MOD*ksm(fc[a-b],MOD-2,MOD)%MOD;
}

int lucas(int n,int m,int MOD){
    if(n<m) return 0;
    if(!n) return 1;
    return lucas(n/MOD,m/MOD,MOD)*getC(n%MOD,m%MOD,MOD)%MOD;
}

int crt(){
    int ans=0;
    for(int i=1;i<=4;i++){
        ans=(ans+a[i]*(P/b[i])%P*ksm(P/b[i],b[i]-2,b[i]))%P;
    }
    return ans;
}

signed main(){
    cin>>n>>g;
    if(g%(P+1)==0){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=4;i++){
        init(b[i]);
        for(int j=1;j*j<=n;j++){
            if(n%j==0){
                a[i]=(a[i]+lucas(n,j,b[i]))%b[i];
                if(j*j!=n){
                    a[i]=(a[i]+lucas(n,n/j,b[i]))%b[i];
                }
            }
        }
    }
    int val=crt();
    cout<<ksm(g,val,P+1)<<'\n';
    return 0;
}
