#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=25;
int n,m,ans,MOD;
string s;

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        for(int i=0;i<MN;i++) mat[i][i]=x;
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]+=mat[i][k]*x.mat[k][j]%MOD;
                }
            }
        }
        return ret;
    }

}F,G;

namespace KMP{
    int pre[MN];

    void initpre(string s){
        pre[1]=0;
        for(int i=2;i<=m;i++){
            int j=pre[i-1];
            while(j>0&&s[i]!=s[j+1]) j=pre[j];
            if(s[i]==s[j+1]) j++;
            pre[i]=j;
        }
        for(int i=0;i<m;i++){
            for(char ch='0';ch<='9';ch++){
                int j=i;
                while(j&&s[j+1]!=ch) j=pre[j];
                if(s[j+1]==ch) ++j;
                G.mat[i][j]++;
            }
        }
    }

}using namespace KMP;

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
    cin>>n>>m>>MOD>>s;
    s=" "+s;
    initpre(s);
    F=ksm(G,n);
    for(int i=0;i<m;i++){
        (ans+=F.mat[0][i])%=MOD;
    }
    cout<<ans;
    return 0;
}
