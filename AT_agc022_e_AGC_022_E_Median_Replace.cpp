#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15,MOD=1e9+7;
string s;
int f[MN][15],g[7][2]={{1,3},{2,0},{1,1},{5,4},{4,4},{6,3},{5,5}};

signed main(){
    cin>>s;
    int n=s.length();
    s=' '+s;
    f[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<7;j++){
            if(s[i+1]!='0'){
                f[i+1][g[j][1]]=(f[i+1][g[j][1]]+f[i][j])%MOD;
            }
            if(s[i+1]!='1'){
                f[i+1][g[j][0]]=(f[i+1][g[j][0]]+f[i][j])%MOD;
            }
        }
    }
    cout<<(f[n][3]+f[n][4])%MOD;
    return 0;
}
