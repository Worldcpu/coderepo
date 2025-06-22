#include<bits/stdc++.h>
#include <cmath>
#define int long long
using namespace std;
constexpr int MN=250,INF=1e18;
int n,t,l;

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=INF){
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                mat[i][j]=INF;
            }
        }
        if(x==INF) return;
        for(int i=0;i<MN;i++) mat[i][i]=x;
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]=min(ret.mat[i][j],max(mat[i][k],x.mat[k][j]));
                }
            }
        }
        return ret;
    }
}adj;

Matrix ksm(Matrix a,int b){
    Matrix ret(0);
    while(b){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>t>>l;
    for(int i=1;i<=t;i++){
        int u,v;
        cin>>u>>v;
        adj.mat[u][v]=i;
    }
    adj=ksm(adj,l);
    for(int i=1;i<=n;i++){
        cout<<(adj.mat[1][i]==INF?-1:adj.mat[1][i])<<'\n';
    }
    return 0;
}
