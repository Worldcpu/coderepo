#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],qwq;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=2;i<=n;i++){
        if(a[i]-a[i-1]==0) continue;
        qwq=gcd(qwq,a[i]-a[i-1]);
        if(qwq==1){
            cout<<2;
            return 0;
        }
    }
    if(qwq>1) cout<<1;
    else cout<<2;


    return 0;
}