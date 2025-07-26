#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353;
int n,a[MN],b[MN],f[MN];
vector<int> pos[MN];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    for(int i=1,j=0,k=0;i<=n;i++){
        while(j<n&&b[j+1]<a[i]) j++;
        while(k<n&&a[k+1]<b[i]) k++;
        pos[k].push_back(j);
    }
    f[0]=1;
    for(int i=1;i<=n;i++){
        f[i]=2*f[i-1]%MOD;
        for(auto p:pos[i]){
            f[i]=(f[i]-f[p]+MOD)%MOD;
        }
    }
    cout<<f[n];

    return 0;
}