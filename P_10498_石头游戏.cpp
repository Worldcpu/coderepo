#include<bits/stdc++.h>
#define int long long
#include <cstdio>
using namespace std;
constexpr int MN=250;
int n,m,T,act,idx[MN][MN],cnt[MN][MN];
string seq[MN];

int gp(int x,int y){
    return (x-1)*m+y;
}

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        for(int i=0;i<MN;i++){
            mat[i][i]=x;
        }
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<=n*m;i++){
            for(int j=0;j<=n*m;j++){
                for(int k=0;k<=n*m;k++){
                    ret.mat[i][j]+=mat[i][k]*x.mat[k][j];
                }
            }
        }
        return ret;
    }

}mat[1144];

Matrix qpow(Matrix a,int b){
    Matrix ret(1);
    while(b){
        if(b&1){
            ret=ret*a;
        }
        a=a*a;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>m>>T>>act;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char x;
            cin>>x;
            idx[i][j]=x-'0'+1;
        }
    }
    for(int i=1;i<=act;i++){
        cin>>seq[i];
    }
    for(int t=1;t<=60;t++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int x=idx[i][j],y=cnt[i][j];
                if(isdigit(seq[x][y])){
                    mat[t].mat[0][gp(i,j)]=seq[x][y]-'0';
                    mat[t].mat[gp(i,j)][gp(i,j)]=1;
                }
                if(seq[x][y]=='N'&&i>1) mat[t].mat[gp(i,j)][gp(i-1,j)]=1;
                if(seq[x][y]=='S'&&i<n) mat[t].mat[gp(i,j)][gp(i+1,j)]=1;
                if(seq[x][y]=='E'&&j<m) mat[t].mat[gp(i,j)][gp(i,j+1)]=1;
                if(seq[x][y]=='W'&&j>1) mat[t].mat[gp(i,j)][gp(i,j-1)]=1;
                cnt[i][j]=(y+1)%seq[x].length();
            }
        }
        mat[t].mat[0][0]=1;
    }
    int maxx=0;
    Matrix sum,ans;
    sum=mat[1];
    for(int i=2;i<=60;i++) sum=sum*mat[i];
    ans.mat[1][0]=1;
    ans=ans*qpow(sum,T/60);
    for(int i=1;i<=T%60;i++) ans=ans*mat[i];
    for(int i=1;i<=n*m;i++){
        maxx=max(maxx,ans.mat[1][i]);
    }
    cout<<maxx;
    return 0;
}
