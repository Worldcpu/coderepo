#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e3+15,ME=1e5+15;
int n,m,f[MN][MN],ans[ME];


int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        f[u][v]=i;
    }
    for(int k=n;k>=1;k--){
        for(int i=1;i<=n;i++){
            if(!f[i][k]) continue;
            int t=f[i][k],lim=(i>k)?(k-1):n;
            for(int j=1;j<=lim;j++){
                f[i][j]=max(f[i][j],min(t,f[k][j]));
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            ans[min(f[i][j],f[j][i])]++;
        }
    }
    ans[m+1]=n;
    for(int i=m;i>=1;i--){
        ans[i]+=ans[i+1];
    }
    for(int i=1;i<=m+1;i++) cout<<ans[i]<<' ';
    return 0;
}