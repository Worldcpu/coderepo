#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MT=10;
int n,MOD;

struct Matrix{
    int mat[MT][MT];

    Matrix(int x=0){
        for(int i=0;i<MT;i++){
            for(int j=0;j<MT;j++){
                mat[i][j]=0;
            }
            mat[i][i]=x;
        }
    }

    friend Matrix operator *(const Matrix &x,const Matrix &y){
        Matrix ret;
        for(int i=0;i<MT;i++){
            for(int j=0;j<MT;j++){
                for(int k=0;k<MT;k++){
                    ret.mat[i][j]=(ret.mat[i][j]+x.mat[i][k]*y.mat[k][j]%MOD)%MOD;
                }
            }
        }
        return ret;
    }

}A,B;

Matrix ksm(Matrix a,int b){
    Matrix ret(1);
    while(b){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}


signed main(){
    cin>>n>>MOD;
    B.mat[2][1]=B.mat[2][2]=B.mat[3][2]=B.mat[3][3]=1;
    A.mat[1][2]=A.mat[1][3]=1;
    for(int i=10;;i*=10){
        B.mat[1][1]=i%MOD;
        if(n<i){
            A=A*ksm(B,n-i/10+1);
            break;
        }
        A=A*ksm(B,i-i/10);
    }
    cout<<A.mat[1][1];
    
    return 0;
}