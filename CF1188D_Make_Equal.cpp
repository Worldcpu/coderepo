#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int f[66][MN],sum[2][MN],a[MN],id[MN],n,nowi;

bool cmp(int x,int y){
    return (a[x]&((1ll<<nowi)-1))<(a[y]&((1ll<<nowi)-1));
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        a[i]=a[n]-a[i];
        id[i]=i;
    }
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int i=0;i<=60;i++){
        nowi=i;
        sort(id+1,id+n+1,cmp);
        for(int j=1;j<=n;j++){
            sum[0][j]=sum[0][j-1];
            sum[1][j]=sum[1][j-1];
            sum[((a[id[j]]>>i)&1)][j]++;
        }
        for(int j=0;j<=n;j++){
            int w,nj;	
            w=sum[1][n-j]+sum[0][n]-sum[0][n-j],nj=sum[1][n]-sum[1][n-j];
			f[i+1][nj]=min(f[i+1][nj],f[i][j]+w);
			w=sum[0][n-j]+sum[1][n]-sum[1][n-j],nj=n-sum[0][n-j];
			f[i+1][nj]=min(f[i+1][nj],f[i][j]+w);
        }
    }
    cout<<f[61][0];
    

    return 0;
}
