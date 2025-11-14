#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;


signed main(){
    cin>>n;
    for(int i=1,j;i<=n;i=j+1){
        j=n/(n/i);
        ans+=(j-i+1)*(n/i); 
    }
    cout<<ans;

    return 0;
}