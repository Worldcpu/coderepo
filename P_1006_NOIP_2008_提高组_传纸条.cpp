#include<bits/stdc++.h>
using namespace std;                         
const int MN=55;
int m,n,a[MN][MN],f[MN][MN][MN][MN];
int main(){
    cin>>m>>n;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){  
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=m;k++){
                for(int p=1;p<=n;p++){
                    f[i][j][k][p]=max({f[i-1][j][k-1][p],f[i][j-1][k][p-1],f[i-1][j][k][p-1],f[i][j-1][k-1][p]})+a[i][j];
                    if(i!=k&&j!=p){
                        f[i][j][k][p]+=a[k][p];
                    }
                }
            }
        }
    }       
    cout<<f[m][n][m][n]<<'\n';
    return 0;
}