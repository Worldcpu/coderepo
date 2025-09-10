#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int sum[MN][MN],mp[MN][MN],n,m;


int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char x;
            cin>>x;
            mp[i][j]=(x=='.');
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i+1<=n&&j+1<=n){
                sum[i][j]=(mp[i][j]&&mp[i+1][j]&&mp[i][j+1]&&mp[i+1][j+1]);
            }else sum[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }
    for(int i=1;i<=m;i++){
        int u,d,l,r;
        cin>>u>>d>>l>>r;
        cout<<sum[d-1][r-1]-sum[u-1][r-1]-sum[d-1][l-1]+sum[u-1][l-1]<<'\n';
    }

    return 0;
}