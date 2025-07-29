#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=150;
int m,a,c,x0,n,MOD;


struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        for(int i=0;i<MN&&x!=0;i++){
            mat[i][i]=x;
        }
    }

    static int Mul(int a,int b){
        int ret=0;
        while(b){
            if(b&1) ret=(ret+a)%m;
            a=(a+a)%m;
            b>>=1;
        }
        return ret;
    }

    friend Matrix operator *(const Matrix &x,const Matrix& y){
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]=(ret.mat[i][j]+Mul(x.mat[i][k],y.mat[k][j]))%m;
                }
            }
        }
        return ret;
    }

}A,G;

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
    cin>>m>>a>>c>>x0>>n>>MOD;
    if(!n){
        cout<<x0;
        return 0;
    }
    G.mat[1][1]=a,G.mat[1][2]=1,G.mat[2][2]=1;
    A.mat[1][1]=x0,A.mat[2][1]=c;
    A=ksm(G,n)*A;
    cout<<A.mat[1][1]%MOD;



    return 0;
}