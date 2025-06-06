#include<bits/stdc++.h>
using namespace std;
constexpr int MN=100,MOD=2009;
int n,t,tot,idx[MN][10];

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        if(!x) return;
        for(int i=0;i<MN;i++) mat[i][i]=x; 
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]+=mat[i][k]*x.mat[k][j];
                    ret.mat[i][j]%=MOD;
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

void initG(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=9;j++){
            idx[i][j]=++tot;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<9;j++){
            G.mat[idx[i][j]][idx[i][j+1]]=1;
        }
    }
}

int main(){
    cin>>n>>t;
    initG();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char c;
            int num;
            cin>>c;
            num=c-'0';
            if(num>0){
                G.mat[idx[i][num]][idx[j][1]]=1;
            }
        }
    }
    A=ksm(G,t);
    cout<<A.mat[1][idx[n][1]]%2009;
    return 0;
}
