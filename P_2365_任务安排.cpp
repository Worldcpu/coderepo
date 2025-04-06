#include<bits/stdc++.h>
#define lk s[i]
#define ll long long
using namespace std;
constexpr int MN=5125;
int n,s;
ll a[MN],sumt[MN],sumc[MN],f[MN];
int main(){
    cin>>n>>s;
    for(int i=1;i<=n;i++){
        ll t,c;
        cin>>t>>c;
        sumt[i]=sumt[i-1]+t;
        sumc[i]=sumc[i-1]+c;
    }
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            f[i]=min(f[i],f[j]+sumt[i]*(sumc[i]-sumc[j])+s*(sumc[n]-sumc[j]));
        }
    }
    cout<<f[n];
    return 0;
}