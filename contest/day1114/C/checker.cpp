#include "../../testlib.h"
#include<bits/stdc++.h>
const int NN = 1e3 + 8;
int a[NN][NN],MOD;
bool get[NN];

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc,argv);
    int n = inf.readInt();
    MOD = n * n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            a[i][j] = ouf.readInt(1,n);

    for(int i = 1; i <= n; ++i){
        memset(get,0,sizeof(get));
        for(int j = 1; j <= n; ++j){
            if(get[a[i][j]]){quitf(_wa,"line %d in the 1st matrix is not a permutation for (1,n)",i);}
            get[a[i][j]] = 1;
        }
    }
    for(int i = 1; i <= n; ++i){
        memset(get,0,sizeof(get));
        for(int j = 1; j <= n; ++j){
            int x = (1 - j + n) % n + 1;
            int y = (i + j - 1) % n + 1;
            if(get[a[i][j]]){quitf(_wa,"the bia crossing (%d,%d) in the 1st matrix is not a permutation for (1,n)",x,y);}
            get[a[i][j]] = 1;
        }
    }

    for(int i = 1; i <= n; ++i)
        for(int j = 1,x; j <= n; ++j){
            if(i + j == n+1) a[i][j] = ouf.readInt(1,n);
            else{
                x = ouf.readInt();
                if(a[i][j] != x)
                    quitf(_wa,"the number is different at (%d,%d),with %d in the 1st matrix ans %d in the 2nd matrix",i,j,a[i][j],x);
            }
        }

    for(int i = 1; i <= n; ++i){
        memset(get,0,sizeof(get));
        for(int j = 1; j <= n; ++j){
            if(get[a[j][i]]){quitf(_wa,"column %d in the 2nd matrix is not a permutation for (1,n)",i);}
            get[a[j][i]] = 1;
        }
    }
    for(int i = 1; i <= n; ++i){
        memset(get,0,sizeof(get));
        for(int j = 1; j <= n; ++j){
            int x = (1 - j + n) % n + 1;
            int y = (i + j - 2) % n + 1;
            if(get[a[x][y]]){quitf(_wa,"the bia crossing (%d,%d) in the 2nd matrix is not a permutation for (1,n)",x,y);}
            get[a[x][y]] = 1;
        }
    }
    quitf(_ok, "The answer is accepted.");
    return 0;
}
