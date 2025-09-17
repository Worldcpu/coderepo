#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int sumx[MN],sumy[MN],sumz[MN],a[MN],n,q;

signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sumx[i]=a[i];
        sumy[i]=i*a[i];
        sumz[i]=i*i*a[i];
    }
    for(int i=1;i<=n;i++){
        sumx[i]+=sumx[i-1];
        sumy[i]+=sumy[i-1];
        sumz[i]+=sumz[i-1];
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        int X = sumx[r]-sumx[l-1];
        int Y = sumy[r]-sumy[l-1];
        int Z = sumz[r]-sumz[l-1];
        cout << (l+r)*Y+(r-l+1)*X-l*r*X-Z << '\n';
    }
    

    return 0;
}