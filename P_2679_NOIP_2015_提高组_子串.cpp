#include<bits/stdc++.h>
using namespace std;
const int MN=1001,MM=201,MOD=1e9+7;
long long f[2][MM][MM][2],now=1;
int n,m,mk;
string a,b;
int main(){
    cin>>n>>m>>mk;
    cin>>a>>b;
    a=' '+a;
    b=' '+b;
    f[0][0][0][0]=f[1][0][0][0]=1;
    for(int i=1;i<=n;i++){
        f[now][0][0][0]=1;
        for(int j=1;j<=m;j++){
            for(int k=1;k<=mk;k++){
                f[now][j][k][0]=(f[now^1][j][k][0]+f[now^1][j][k][1])%MOD;
                if(a[i]==b[j]){
                    f[now][j][k][1]=(f[now^1][j-1][k-1][0]+(f[now^1][j-1][k-1][1]+f[now^1][j-1][k][1])%MOD)%MOD;
                }else f[now][j][k][1]=0;
            }
        }
        now^=1;
    }
    cout<<(f[now^1][m][mk][0]+f[now^1][m][mk][1])%MOD;
    return 0;
}