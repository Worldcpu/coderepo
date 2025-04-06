#include<iostream>
#include<cmath>
#define int long long
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
    if(n>1){
        ans=ans/n*(n-1);
    }
    return ans;
}
signed main(){
    int n,ret=0;
    cin>>n;
    for(int i=1;i<=sqrt(n);i++){
        if(n%i==0){
            ret+=i*phi(n/i);
            if(i*i!=n) ret+=n/i*phi(i);
        }
    }
    cout<<ret;
    return 0;
}