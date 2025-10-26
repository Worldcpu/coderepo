#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;
constexpr int MN=55;
int n,p,matx[MN][MN],maty[MN][MN];
int matA[MN][MN];
int b[MN][MN];

int mod(int x,int P){ return (x%P+P)%P; }

void solve_case(InStream &inf, InStream &ouf, InStream &ansf){
    n = inf.readInt(1,50,"n");
    p = inf.readInt(2,1000000,"p"); // 模数

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) matx[i][j]=inf.readInt(0,p-1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) maty[i][j]=inf.readInt(0,p-1);
    }

    string ja = ansf.readWord();
    string pa = ouf.readWord();

    if(ja=="No" && pa=="No"){ 
        return;
    }else if(ja=="No" && pa!="No"){
        quitf(_wa,"Expected No, but participant output Yes");
    }else if(pa=="No"){
        quitf(_wa,"Participant output No but solution exists");
    }

    // 参赛者输出 Yes + b[i][j] 矩阵
    if(pa!="Yes") quitf(_wa,"First word must be Yes or No");

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            b[i][j]=ouf.readInt(0,p-1);
        }
    }

    // 检查每个格子最终增量是否等于差矩阵
    // 先计算差矩阵
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            matA[i][j] = mod(maty[i][j]-matx[i][j],p);
        }
    }

    // 计算每个格子实际被加次数
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int rsum=0,csum=0;
            for(int k=1;k<=n;k++) rsum=(rsum+b[i][k])%p;
            for(int k=1;k<=n;k++) csum=(csum+b[k][j])%p;
            int total = mod(rsum+csum-b[i][j],p);
            if(total!=matA[i][j]){
                quitf(_wa,"Cell (%d,%d) increment %d != required %d",i,j,total,matA[i][j]);
            }
        }
    }

    quitf(_ok,"Correct Yes output");
}

int main(int argc,char* argv[]){
    registerTestlibCmd(argc,argv);
    int T = inf.readInt(1,50,"T");
    while(T--){
        solve_case(inf,ouf,ans);
    }
    return 0;
}
