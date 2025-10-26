#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,r,K,a[MN],cf[MN];


signed main(){
    cin>>n>>K>>r;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cf[i]=a[i]-a[i-1];
    }
    for(int i=1;i<=n-K+1;i++){
        int val=cf[i];
        cf[i]=0;
        cf[i+K]+=val;
    }
    for(int i=1;i<=n;i++){
        if(cf[i]&&cf[i]%r!=0){
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";

    return 0;
}