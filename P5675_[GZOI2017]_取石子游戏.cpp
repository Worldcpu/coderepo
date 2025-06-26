#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=1e9+7;
int f[MN][MN],ans,n,a[MN];

void solvedp(int x){
    memset(f,0,sizeof(f));
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<256;j++){
            if(i==x) f[i][j]=f[i-1][j];
            else f[i][j]=(f[i-1][j]+f[i-1][j^a[i]])%MOD;
        }
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        solvedp(i);
        for(int j=a[i];j<256;j++){
            (ans+=f[n][j])%=MOD;
        }
    }
    cout<<ans;
    return 0;
}
