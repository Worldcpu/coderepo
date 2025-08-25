#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e3+15;
int n,q,a[MN],p[MN];


signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    int ans=0;
    while(q--){
        int op,l,r,k;
        cin>>op>>l>>r;
        l^=ans;
        r^=ans;
        if(op==1){
            cin>>k;
            k^=ans;
            for(int i=l;i<=r;i++) a[i]+=k;
        }else{
            int ret=0;
            for(int i=l;i<=r;i++) ret+=a[p[i]];
            cout<<(ans=ret)<<'\n';
        }
    }

    return 0;
}