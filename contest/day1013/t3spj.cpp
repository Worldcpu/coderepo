#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;

constexpr int MN = 55;
int matx[MN][MN], maty[MN][MN], n, MOD;

void apply_operations(const vector<tuple<int,int,int>>& ops, int mat[MN][MN]){
    for(auto &t : ops){
        int x,y,c;
        tie(x,y,c) = t;
        for(int i=1;i<=n;i++){
            mat[x][i] = (mat[x][i]+c)%MOD;
            mat[i][y] = (mat[i][y]+c)%MOD;
        }
        mat[x][y] = (mat[x][y]-c+MOD)%MOD; // 修正重复加
    }
}

int main(int argc, char* argv[]){
    registerTestlibCmd(argc, argv);

    int T = inf.readInt(1,50,"T");
    for(int t=1; t<=T; t++){
        n = inf.readInt(1,50,"n");
        MOD = inf.readInt(2,1e9,"MOD");
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                matx[i][j] = inf.readInt(0,MOD-1);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                maty[i][j] = inf.readInt(0,MOD-1);

        string ja = ans.readToken(); // Judge 输出
        string pa = ouf.readToken(); // 参赛者输出

        if(ja=="No" && pa=="No") continue;
        if(ja=="No" && pa=="Yes") quitf(_wa,"Case %d: Judge says No but contestant says Yes", t);
        if(ja=="Yes" && pa=="No") quitf(_wa,"Case %d: Judge says Yes but contestant says No", t);

        vector<tuple<int,int,int>> ops;
        if(pa=="Yes"){
            // 读参赛者操作，直到下一组或文件末尾
            while(!ouf.seekEof()){
                string tok = ouf.readToken();
                if(tok=="Yes" || tok=="No") {
                    ouf.unreadChar(tok); // 回退，用于下一组判断
                    break;
                }
                int x = to_int(tok);
                int y = ouf.readInt(1,n);
                int c = ouf.readInt(0,MOD-1);
                if(c>0) ops.push_back({x,y,c});
            }
        }

        int tmp[MN][MN];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                tmp[i][j] = matx[i][j];

        apply_operations(ops, tmp);

        // 检查矩阵是否达到目标
        bool ok = true;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(tmp[i][j] != maty[i][j]){
                    ok=false;
                    break;
                }
            }
            if(!ok) break;
        }
        if(!ok) quitf(_wa,"Case %d: Operations do not produce the target matrix", t);
    }

    quitf(_ok,"All test cases passed");
}
