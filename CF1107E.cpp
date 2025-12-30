#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=114;
int f[MN][MN][MN],n,a[MN];
string st;

signed main(){
    cin>>n>>st;
    st=" "+st;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int l=n;l>=1;l--){
        for(int r=l;r<=n;r++){
            for(int k=0;k<n;k++){
                f[l][r][k]=f[l][r-1][0]+a[k+1];
                for(int p=l;p<r;p++){
                    if(st[p]==st[r]){
                        f[l][r][k]=max(f[l][r][k],f[p+1][r-1][0]+f[l][p][k+1]);
                    }
                }
            }
        }
    }
    cout<<f[1][n][0];
    return 0;
}