#include<bits/stdc++.h>
#include <csetjmp>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,a[MN],b[MN],f[MN],g[MN];

namespace FWT{
#define int long long

constexpr int MOD=998244353,inv2=499122177,Cor[2][2]  ={{1,0},{1,1}},Cand[2][2] ={{1,1},{0,1}},Cxor[2][2] ={{1,1},{1,MOD-1}};
constexpr int ICor[2][2] ={{1,0},{MOD-1,1}},ICand[2][2]={{1,MOD-1},{0,1}},ICxor[2][2]={{inv2,inv2},{inv2,MOD-inv2}};

void FWT(int f[],const int c[2][2],int n){
    for(int len=1;len<n;len<<=1){
        for(int p=0;p<n;p+=len*2){
            for(int i=p;i<p+len;i++){
                int tmp=f[i];
                f[i]=(c[0][0]*f[i]+c[0][1]*f[i+len])%MOD;
                f[i+len]=(c[1][0]*tmp+c[1][1]*f[i+len])%MOD;
            }
        }
    }
}

void BitMul(int f[],int g[],const int c[2][2],const int ic[2][2],int len){
    FWT(f,c,len);
    FWT(g,c,len);
    for(int i=0;i<len;i++) f[i]=f[i]*g[i]%MOD;
    FWT(f,ic,len);
}

#undef int
}

void solveor(){
    for(int i=0;i<n;i++){
        a[i]=f[i];
        b[i]=g[i];
    }
    FWT::BitMul(a,b,FWT::Cor,FWT::ICor,n);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
}


void solveand(){
    for(int i=0;i<n;i++){
        a[i]=f[i];
        b[i]=g[i];
    }
    FWT::BitMul(a,b,FWT::Cand,FWT::ICand,n);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
}

void solvexor(){
    for(int i=0;i<n;i++){
        a[i]=f[i];
        b[i]=g[i];
    }
    FWT::BitMul(a,b,FWT::Cxor,FWT::ICxor,n);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
}

signed main(){
    cin>>n;
    n<<=1;
    for(int i=0;i<n;i++){
        cin>>f[i];
    }
    for(int i=0;i<n;i++){
        cin>>g[i];
    }
    solveor();
    cout<<'\n';
    solveand();
    cout<<'\n';
    solvexor();
    return 0;
}
