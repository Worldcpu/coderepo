#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=1e9+7;
int n,m,sums[MN],sumt[MN],f[MN][MN];
char s[MN],t[MN];


signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        t[i]=s[i];
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        sort(s+l,s+r+1);
        sort(t+l,t+r+1);
        reverse(t+l,t+r+1);
    }
    for(int i=1;i<=n;i++){
        sums[i]=sums[i-1]+(s[i]=='1');
        sumt[i]=sumt[i-1]+(t[i]=='1');
    }   
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=sums[i];j<=sumt[i];j++){
            if(!j){
                f[i][j]=f[i-1][j];
            }
            else f[i][j]=(f[i-1][j]+f[i-1][j-1])%MOD;
        }
    }
    cout<<f[n][sums[n]];
    return 0;
}