#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=2048;
int a[MN],m,b[MN],n;
ll f[MN][MN],ans=1e18;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    m=unique(b+1,b+1+n)-b-1;
    //cout<<"M:"<<m<<'\n';
    for(int i=1;i<=n;i++){
        ll minn=f[i-1][1];
        for(int j=1;j<=m;j++){
            minn=min(minn,f[i-1][j]);
            f[i][j]=minn+abs(b[j]-a[i]);
        }
    }
    for(int i=1;i<=m;i++){
        ans=min(ans,f[n][i]);
    }
    reverse(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        ll minn=f[i-1][1];
        for(int j=1;j<=m;j++){
            minn=min(minn,f[i-1][j]);
            f[i][j]=minn+abs(b[j]-a[i]);
        }
    }
    for(int i=1;i<=m;i++){
        ans=min(ans,f[n][i]);
    }
    cout<<ans;
    return 0;
}