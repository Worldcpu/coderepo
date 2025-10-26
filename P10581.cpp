#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=114,MOD=998244353;
int n,m,nxt[MN],ans;
string st;

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        for(int i=0;i<MN;i++){
            mat[i][i]=x;
        }
    }

    friend Matrix operator*(const Matrix &x,const Matrix &y){
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    ret.mat[i][j]=(ret.mat[i][j]+x.mat[i][k]*y.mat[k][j]%MOD)%MOD;
                }
            }
        }
        return ret;
    }
}A,B;

Matrix ksm(Matrix a,int b){
    Matrix ret(1);
    while(b>0){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

int gpos(int x,int y){
    return y*(m+1)+x;
}

void initnxt(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        while(j&&st[i]!=st[j+1]) j=nxt[j];
        if(st[j+1]==st[i]) j++;
        nxt[i]=j;
    }   
}

signed main(){
    cin>>st>>n;
    m=st.length();
    st=" "+st;
    initnxt();
    for(int i=0;i<=2;i++){
        for(int j=0;j<m;j++){
            for(int k='a';k<='z';k++){
                int it=j;
                while(it&&st[it+1]!=(char)k) it=nxt[it];
                if(st[it+1]==k) it++;
                if(it==m){
                    if(i!=2){
                        B.mat[gpos(j,i)][gpos(nxt[it],i+1)]++;
                    }
                }else B.mat[gpos(j,i)][gpos(it,i)]++;
            }
        }
    }
    A.mat[0][0]=1;
    A=A*ksm(B,n);
    for(int j=0;j<=m;j++){
        ans=(ans+A.mat[0][gpos(j,2)])%MOD;
    }
    cout<<ans;
    return 0;
}
