#include<bits/stdc++.h>
using namespace std;
const int MN=1024,INF=1e9;
int n;
int a[MN],sum[MN],f1[MN][MN],f2[MN][MN];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]+=sum[i-1]+a[i];
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=2*n;l++){
            int r=l+len-1;
            f1[l][r]=0;
            f2[l][r]=INF;
            for(int k=l;k<r;k++){
                f1[l][r]=max(f1[l][r],f1[l][k]+f1[k+1][r]+sum[r]-sum[l-1]);
                f2[l][r]=min(f2[l][r],f2[l][k]+f2[k+1][r]+sum[r]-sum[l-1]);
            }
        }
    }
    int ans1=0,ans2=INF;
    for(int i=1;i<=n;i++){
        ans1=max(ans1,f1[i][i+n-1]);
        ans2=min(ans2,f2[i][i+n-1]);
    }
    cout<<ans2<<'\n'<<ans1;
    return 0;
}