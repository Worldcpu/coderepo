#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        int a1,b1,a0,b0,ans=0;
        cin>>a0>>a1>>b0>>b1;
        for(int i=1;i*i<=b1;i++){
            if(b1%i) continue;
            if(i%a1==0&&gcd(i/a1,a0/a1)==1&&gcd(b1/b0,b1/i)==1){
                ans++;
            }
            int y=b1/i;
            if(i==y) continue;
            if(y%a1==0&&gcd(y/a1,a0/a1)==1&&gcd(b1/b0,b1/y)==1) ans++;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
