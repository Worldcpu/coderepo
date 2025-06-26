#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
    int n;
    cin>>n;
    while(n){
        if(n==1){
            cout<<1;
            break;
        }
        if(n==2){
            cout<<2;
            break;
        }
        int a=1,b=2,c=3;
        while(c<n) a=b,b=c,c=a+b;
        if(c==n){
            cout<<n;
            break;
        }
        n-=b;
    }
    return 0;
}
