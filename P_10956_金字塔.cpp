#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=50,MOD=1e9;
ll n,f[MN][MN];
int main(){
    string s;
    cin>>s;
    n=s.size();
    s=' '+s;
    for(int i=1;i<=n;i++){
        f[i][i]=1;
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            if(s[l]!=s[r]){
                f[l][r]=0;
            }else{
                f[l][r]+=f[l+1][r-1];
                f[l][r]%=MOD;
                for(int k=l+2;k<=r-2;k++){
                    if(s[l]==s[k]){
                        f[l][r]+=f[l+1][k-1]*f[k][r];
                        f[l][r]%=MOD;
                    }
                }
            }
        }
    }
    cout<<f[1][n]%MOD;
    return 0;
}