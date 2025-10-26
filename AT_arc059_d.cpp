#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=1e9+7;
int n,m;
int f[MN][MN];
string st;

signed main(){
    cin>>n>>st;
    m=st.length();
    st=" "+st;
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            f[i][j]=(f[i][j]+f[i-1][max(j-1,0ll)]+f[i-1][j+1]*2%MOD)%MOD;
        }
    }
    cout<<f[n][m];
    return 0;
}