#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MB=300;
int n,m,a[MN],f[MB+15][MN];


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=MB;i++){
        for(int j=n;j>=1;j--){
            f[i][j]=(j+a[j]+i>n)?1:f[i][j+a[j]+i]+1;
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int p,k,ans=0;
        cin>>p>>k;
        if(k>=MB){
            while(p<=n){
                ans++;
                p+=a[p]+k;
            }
        }else ans=f[k][p];
        cout<<ans<<'\n';
    }
    return 0;
}
