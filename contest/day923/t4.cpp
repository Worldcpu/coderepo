#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,p,q,a[MN],b[MN],ans;
char t[MN];

signed main(){
    cin>>n>>m>>p>>q;
    for(int i=1;i<=n;i++){
        cin>>t[i]>>a[i];
        b[i]=i;
    }
    do{
        int cst=0,x=1;
        for(int i=1;i<=n;i++){
            if(b[i]==i) continue;
            cst+=(t[b[i]]=='A'?p:q);
        }
        if(cst>m) continue;
        for(int i=1;i<=n;i++){
            if(t[b[i]]=='A'){
                x=x+a[b[i]];
            }else x=x*a[b[i]];
        }
        ans=max(ans,x);
        for(int i=1;i<=n;i++) cerr<<b[i]<<' ';
        cerr<<'\n';
    }while(next_permutation(b+1,b+1+n));
    cout<<ans;

    return 0;
}