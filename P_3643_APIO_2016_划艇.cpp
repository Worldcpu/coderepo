#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1145+15,MOD=1e9+7;
int f[MN][MN],sum[MN],L[MN],R[MN],b[MN],tot,n,inv[MN];

void init(){
    inv[0]=inv[1]=1;
    for(int i=2;i<MN;i++){
        inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
    }
}

signed main(){
    init();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        R[i]++;
        b[++tot]=L[i];
        b[++tot]=R[i];
    }
    sort(b+1,b+1+tot);
    tot=unique(b+1,b+1+tot)-b-1;
    for(int i=1;i<=n;i++){
        L[i]=lower_bound(b+1,b+1+tot,L[i])-b;
        R[i]=lower_bound(b+1,b+1+tot,R[i])-b;
    }
    f[0][0]=1;
    for(int i=0;i<=tot;i++){
        sum[i]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=L[i];j<R[i];j++){
            int len=b[j+1]-b[j];
            for(int k=i;k>=2;k--){
                f[j][k]=(f[j][k]+(len-k+1)*inv[k]%MOD*f[j][k-1]%MOD)%MOD;
            }
            f[j][1]=(f[j][1]+sum[j-1]*len%MOD)%MOD;
        }
        for(int j=1;j<=tot;j++){
            sum[j]=sum[j-1];
            for(int k=1;k<=i;k++){
                sum[j]=(sum[j]+f[j][k])%MOD;
            }
        }
    }
    cout<<sum[tot]-1;
    return 0;
}