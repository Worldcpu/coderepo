#include<bits/stdc++.h>
using namespace std;
const int MOD=1000;
int n;
struct matrix{
    int mt[10][10]{};
    matrix operator *(const matrix &x)const{
        matrix ret;
        for(int i=1;i<=8;i++){
            for(int j=1;j<=8;j++){
                for(int k=1;k<=8;k++){
                    ret.mt[i][j]+=mt[i][k]*x.mt[k][j]%MOD;
                    ret.mt[i][j]%=MOD;
                }
            }
        }
        return ret;
    }
};

matrix qpow(matrix x,int k){
    matrix ans;
    for(int i=1;i<=8;i++){
        ans.mt[i][i]=1;
    }
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
matrix zy;
int main(){
    cin>>n;
    for(int i=1;i<=8;i++){
        if(i==5) continue;
        zy.mt[i][i-1]=zy.mt[i][i+1]=1;
    }
    zy.mt[1][8]=zy.mt[8][1]=1;
    cout<<qpow(zy,n).mt[1][5];
    return 0;
}