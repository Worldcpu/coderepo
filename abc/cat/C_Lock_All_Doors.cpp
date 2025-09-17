#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,R,a[MN];

signed main(){
    cin>>n>>R;
    for(int i=1;i<=n;i++) cin>>a[i];
    int cntz=0,zl=n+1, zr=0;
    for(int i=1;i<=n;i++){
        if(a[i]==0){
            cntz++;
            zl=min(zl,i);
            zr=max(zr,i);
        }
    }
    if(cntz==0){
        cout<<0<<"\n";
        return 0;
    }
    int L = min(R+1, zl),RR = max(R, zr),cnt1=0;
    for(int i=L;i<=RR;i++) if(a[i]==1) cnt1++;
    cout<<cntz+2*cnt1;
    return 0;
}
