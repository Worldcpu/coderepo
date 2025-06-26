#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int L[MN][MN],R[MN][MN],n,a[MN];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        L[i][i]=R[i][i]=a[i];
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            int x=a[r],xl=L[l][r-1],xr=R[l][r-1];
            if(x==xr) L[l][r]=0;
            else if(x>=xl&&x<xr) L[l][r]=x+1;
            else if(x>xr&&x<=xl) L[l][r]=x-1;
            else L[l][r]=x;
            x=a[l],xl=L[l+1][r],xr=R[l+1][r];
            if(x==xl) R[l][r]=0;
            else if(x>=xr&&x<xl) R[l][r]=x+1;
            else if(x>xl&&x<=xr) R[l][r]=x-1;
            else R[l][r]=x;
        }
    }
    if(L[2][n]==a[1]) cout<<0<<'\n';
    else cout<<1<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
