#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int a[MN],n,x;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        x^=a[i];
    }
    if(!x){
        cout<<"lose";
        return 0;
    }
    for(int i=1;i<=n;i++){
        if((a[i]^x)<a[i]){
            cout<<a[i]-(a[i]^x)<<" "<<i<<'\n';
            a[i]^=x;
            break;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
