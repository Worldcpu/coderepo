#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200;
int f[MN],g[MN][MN],h[MN][MN],a[MN],n;

int calc(int l,int r){
    int res=g[r][r]-g[l-1][r]-g[r][l-1]+g[l-1][l-1];
    if(r==n){
        return res;
    }else{
        res+=h[r][n]-h[r][r]-h[l-1][n]+h[l-1][r];
        return res;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            g[min(a[i],a[j])][max(a[i],a[j])]+=(a[i]<a[j]);
            h[min(a[i],a[j])][max(a[i],a[j])]+=(a[i]>a[j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g[i][j]+=g[i][j-1]+g[i-1][j]-g[i-1][j-1];
            h[i][j]+=h[i][j-1]+h[i-1][j]-h[i-1][j-1];
        }
    }

    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            f[i]=min(f[i],f[j]+calc(j+1,i));
        }
    }
    cout<<f[n];
    return 0;
}