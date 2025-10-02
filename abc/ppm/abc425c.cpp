#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int sum[MN],n,q,py;

inline int get(int l,int r){
    if(l>r) return 0;
    return sum[r]-sum[l-1];
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>sum[i];
        sum[i]+=sum[i-1];
    }
    while(q--){
        int op,l,r,x;
        cin>>op;
        if(op==1){
            cin>>x;
            py=(py+x%n+n)%n;
        }else{
            cin>>l>>r;
            int L=(py+l-1)%n+1;
            int R=(py+r-1)%n+1;
            cerr<<L<<' '<<R<<'\n';
            if(L<=R) cout<<get(L,R)<<"\n";
            else cout<<get(L,n)+get(1,R)<<"\n";
        }
    }
    return 0;
}
