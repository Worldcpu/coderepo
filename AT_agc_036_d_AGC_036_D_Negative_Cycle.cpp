#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e3+15,INF=1e18;
int n,a[MN][MN],b[MN][MN],f[MN][MN],ans;

int val(int k,int j,int i){
	return b[j+1][i]+a[n][j]-a[i][j]-a[n][k]+a[i][k];
}

signed main(){
    cin>>n;
    ans=INF;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j) cin>>a[i][j];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=i;j<=n;j++){
            b[i][j]=b[i+1][j]+b[i][j-1]-b[i+1][j-1]+a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
        }
    }
    for(int i=1;i<n;i++){
        f[i][0]=val(0,0,i);
        ans=min(ans,f[i][0]+val(0,i,n));
        for(int j=1;j<i;j++){
            f[i][j]=INF;
            for(int k=0;k<j;k++){
                f[i][j]=min(f[i][j],f[j][k]+val(k,j,i));
            }
            ans=min(ans,f[i][j]+val(j,i,n));
        }
    }
    cout<<ans;
    return 0;
}