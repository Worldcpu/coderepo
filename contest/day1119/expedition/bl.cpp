#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MS=1024,MN=5e4+15,ML=10;
int n,q,ans,a[MN],b[MN];
bitset<MN> bit[MS];

void solve(int l,int r,int x){
    int res=0;
    for(int i=l;i<=r;i++){
        if((x|a[i])==x){
            res+=b[i];
            x-=a[i];
        }
    }
    ans^=res;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    cin>>q;
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        solve(l,r,x);
    }
    cout<<ans<<'\n';
    return 0;
}