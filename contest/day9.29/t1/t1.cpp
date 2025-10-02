#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int pre[MN],c,n,q;


signed main(){
    freopen("cycle.in","r",stdin);
    freopen("cycle.out","w",stdout);
    cin>>c>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>pre[i];
        pre[i]+=pre[i-1];
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        int mid=(r-l+1)>>1;
        cout<<2*((pre[r]-pre[r-mid])-(pre[l+mid-1]-pre[l-1]))<<'\n';
    }

    return 0;
}