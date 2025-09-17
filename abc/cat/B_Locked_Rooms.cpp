#include<bits/stdc++.h>
using namespace std;
constexpr int MN=150;
int n,a[MN],lmx,rmn;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    lmx=0,rmn=n;
    for(int i=1;i<=n;i++){
        if(a[i]==1) break;
        lmx=i;
    }
    for(int i=n;i>=1;i--){
        if(a[i]==1) break;
        rmn=i-1;
    }
    int ans = max(0, rmn-lmx-1);
    cout<<ans<<"\n";

    return 0;
}
