#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=150,MOD=45989;
struct Edge{
    int u,v;
}e[MN];
int n,m,T,s,t,tot;

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

signed main(){
    cin>>n>>m>>T>>s>>t;
    s++;
    t++;
    e[++tot].u=0;
    e[tot].v=s;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        u++,v++;
        e[++tot].u=u;
        e[tot].v=v;
        e[++tot].u=v;
        e[tot].v=u;
    }
    for(int i=1;i<=tot;i++){
        for(int j=1;j<=tot;j++){
            if(i!=j&&i!=(j^1)){
                if(e[i].v==e[j].u) A.mat[i][j]=1;
            }
        }
    }
    Matrix ret=ksm(A,T);
    int ans=0;
    for(int i=1;i<=tot;i++){
        if(e[i].v==t){
            ans=(ans+ret.mat[1][i])%MOD;
        }
    }
    cout<<ans;
}
