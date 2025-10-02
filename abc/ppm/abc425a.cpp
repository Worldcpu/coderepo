
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        ans+=(i&1?-1:1)*i*i*i;
    }
    cout<<ans;

    return 0;
}