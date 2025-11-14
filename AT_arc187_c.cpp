#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int f[MN][MN],a[MN],n,cnt[MN],num[MN],sum[MN][MN],vis[MN];

bool w(int x,int y){
    if(a[x]>0) return a[x]==y;
    else return !vis[y];
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]!=-1) vis[a[i]]=i;
        cnt[i]=cnt[i-1]+(a[i]==-1);
    }
    for(int i=1;i<=n;i++){
        num[i]=num[i-1]+(!vis[i]);
    }
    f[0][0]=1;
    for(int i=0;i<=n;i++){
        sum[0][i]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!vis[j]||vis[j]>=i){
                f[i][j]=(f[i][j]+sum[i-1][j-1])%MOD;
            }
            if(a[i-1]!=-1){
                if(a[i-1]<j) f[i][j]=(f[i][j]+f[i-1][j])%MOD;                
            }else f[i][j]=(f[i][j]+f[i-1][j]*(num[j-1]-cnt[i-1]+1)%MOD)%MOD;
            sum[i][j]=(sum[i][j-1]+f[i][j]*w(i,j))%MOD;
        }
    }
    cout<<f[n][n];
    return 0;
}