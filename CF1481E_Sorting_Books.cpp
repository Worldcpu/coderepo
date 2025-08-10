#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int f[MN],cnt[MN],n,a[MN],L[MN],R[MN];


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!L[a[i]]) L[a[i]]=i;
        R[a[i]]=i;
    }
    for(int i=n;i>=1;i--){
        f[i]=f[i+1];
        cnt[a[i]]++;
        if(i!=L[a[i]]) f[i]=max(f[i],cnt[a[i]]);
        else f[i]=max(f[i],f[R[a[i]]+1]+cnt[a[i]]);
    }
    cout<<n-f[1];

    return 0;
}
