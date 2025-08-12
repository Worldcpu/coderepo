#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15;
int n,m,lim,a[MN],f[MN];

signed main(){
    cin>>n>>m;
    lim=(1<<__lg(n)+1)-1;
    for(int i=1;i<=n;i++){
        cin>>f[n-i];
    }
    for(int i=0;i<=__lg(n);i++){
        for(int s=1;s<=lim;s++){
            if(s&(1<<i)){
                f[s]^=f[s^(1<<i)];
            }
        }
    }
    for(int i=0;i<m;i++){
        cout<<f[~i&lim]<<" ";
    }

    return 0;
}