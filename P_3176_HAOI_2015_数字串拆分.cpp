#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=10,MOD=998244353;
int m,len,ans;
string s;

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        if(x==0) return;
        for(int i=0;i<MN;i++){
            mat[i][i]=x;
        }
    }

    void init(int x){
        memset(mat,0,sizeof(mat));
        if(x==0) return;
        for(int i=0;i<MN;i++){
            mat[i][i]=x;
        }
    }

    void initf(){
        for(int i=0;i<m;i++) mat[i][m-1]=1;
        for(int i=1;i<m;i++) mat[i][i-1]=1;
    }
    
    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]+=mat[i][k]*x.mat[k][j]%MOD;
                    ret.mat[i][j]%=MOD;
                }
            }
        }
        return ret;
    }

    Matrix operator+(const Matrix &x)const{
        Matrix ret;
         for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                ret.mat[i][j]=(mat[i][j]+x.mat[i][j])%MOD;
            }
        }
        return ret;
    }

}pw[520],f[520][520],g[520];

Matrix ksm(Matrix a,int b){
    Matrix ret(1);
    while(b>0){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>s>>m;
    len=s.length();
    s=' '+s;
    pw[0].initf();
    for(int i=1;i<len;i++) pw[i]=ksm(pw[i-1],10);
    for(int i=1;i<=len;i++){
        for(int j=i;j>=1;j--){
            if(i!=j){
                f[j][i]=f[j+1][i]*ksm(pw[i-j],s[j]-'0');
            }else{
                f[j][i]=ksm(pw[0],s[j]-'0');
            }
        }
    }
    g[0].init(1);
    for(int i=1;i<=len;i++){
        for(int j=0;j<i;j++){
            g[i]=g[i]+(g[j]*f[j+1][i]);
        }
    }
    for(int i=0;i<m;i++) ans=(ans+g[len].mat[0][i])%MOD;
    cout<<ans;
    return 0;
}
