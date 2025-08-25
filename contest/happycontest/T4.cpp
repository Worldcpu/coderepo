#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,MM=105;
int n;
bitset<MN> f[MM];

int main(){
    cin>>n;
    f[0][0]=1;
    for(int i=1,l,r;i<=n;i++){
        cin>>l>>r;
        for(int k=l;k<=r;k++){
            f[i]|=f[i-1]<<k*k;
        }
    }
    cout<<f[n].count();
    return 0;
}