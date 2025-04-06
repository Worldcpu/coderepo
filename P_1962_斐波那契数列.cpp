#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD=1e9+7,MT=5;
struct matrix{
    ll mt[MT][MT]{};
    matrix operator *(const matrix &x){
        matrix ret;
        for(int i=1;i<=2;i++){
            for(int j=1;j<=2;j++){
                for(int k=1;k<=2;k++){
                    ret.mt[i][j]+=mt[i][k]*x.mt[k][j]%MOD;
                    // ret.mt[i][j]%=MOD;
                }
            }
        }
        return ret;
    }
};
ll n;

matrix qp(matrix x,matrix ans,ll k){
    while (k)
    {
        if(k&1){
            ans=ans*x;
        }
        x=x*x;
        k>>=1;
    }
    return ans;
}
matrix ans,base;
int main(){
    cin>>n;
    if(n<2){
        cout<<n;
        return 0;
    }
    base.mt[1][1]=base.mt[1][2]=base.mt[2][1]=1;
    ans.mt[1][1]=ans.mt[1][2]=1;
    cout<<qp(base,ans,n-2).mt[1][1]%MOD;
    return 0;
}