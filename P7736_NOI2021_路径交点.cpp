#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=620,MOD=998244353;
int n,K,m[MN];

struct Matrix{
    int mat[MN][MN],n,m;

    Matrix(int x=0,int y=0){
        n=x,m=y;
        clear();
    }

    void clear(){
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                mat[i][j]=0;
            }
        }
    }

    friend Matrix operator*(const Matrix &x,const Matrix &y){
        Matrix ret(x.n,y.m);
        for(int i=0;i<=ret.n;i++){
            for(int j=0;j<=ret.m;j++){
                for(int k=0;k<=x.m;k++){
                    (ret.mat[i][j]+=x.mat[i][k]*y.mat[k][j]%MOD)%=MOD;
                }
            }
        }
        return ret;
    }

    void print(){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cerr<<mat[i][j]<<" ";
            }
            cerr<<'\n';
        }
    }

    int det(){
        int ret=1,w=1;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                while(mat[i][i]){
                    int div=mat[j][i]/mat[i][i];
                    for(int k=i;k<=n;k++){
                        mat[j][k]=(mat[j][k]-div*mat[i][k]%MOD+MOD)%MOD;
                    }
                    swap(mat[i],mat[j]);
                    w=-w;
                }
                swap(mat[i],mat[j]);
                w=-w;
            }
        }
        for(int i=1;i<=n;i++){
            ret=mat[i][i]*ret%MOD;
        }
        ret=ret*w%MOD;
        return (ret+MOD)%MOD;
    }

}a[MN];

void solve(){
    cin>>K;
    for(int i=1;i<=K;i++){
        int qwq;
        cin>>qwq;
        a[i].n=qwq;
    }
    for(int i=1;i<K;i++){
        a[i].m=a[i+1].n;
    }
    for(int i=1;i<K;i++){
        cin>>m[i];
        a[i].clear();
    }
    for(int i=1;i<K;i++){
        for(int j=1;j<=m[i];j++){
            int u,v;
            cin>>u>>v;
            a[i].mat[u][v]=1;
        }
    }
    for(int i=2;i<K;i++){
        a[1]=a[1]*a[i];
    }
    cout<<a[1].det()<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
