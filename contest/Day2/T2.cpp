#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55,MOD=2017;
int n,m,t,ans;

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        if(!x) return;
        for(int i=0;i<MN;i++) mat[i][i]=x;
    }

    Matrix operator*(const Matrix x)const{
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
}A;

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
    freopen("cola.in","r",stdin);
    freopen("cola.out","w",stdout);
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        A.mat[i][0]=1;
        A.mat[i][i]=1;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        A.mat[u][v]=1;
        A.mat[v][u]=1;
    }
    cin>>t;
    A=ksm(A,t);
    for(int i=0;i<=n;i++){
        (ans+=A.mat[1][i])%=MOD;
    }
    cout<<ans;

    return 0;
}
