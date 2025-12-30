#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
static int dirmat[5005][5005];   // 1 means u<v
long long dp[5005][5005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> op(n+1);
    for(int i=1;i<=n;i++) cin >> op[i];

    // Build dir matrix for constraints
    // dir[u][v] = 1 means a_u < a_v
    // otherwise 0. Check contradictions.

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            // op[j]=0 (Lmin): a_j < a_i => j -> i
            if(op[j] == 0){
                if(dirmat[i][j] == 1){ cout << 0; return 0; }
                dirmat[j][i] = 1;
            }
            // op[j]=1 (Lmax): a_j > a_i => i -> j
            if(op[j] == 1){
                if(dirmat[j][i] == 1){ cout << 0; return 0; }
                dirmat[i][j] = 1;
            }
            // op[i]=2 (Rmin): a_i < a_j => i -> j
            if(op[i] == 2){
                if(dirmat[j][i] == 1){ cout << 0; return 0; }
                dirmat[i][j] = 1;
            }
            // op[i]=3 (Rmax): a_i > a_j => j -> i
            if(op[i] == 3){
                if(dirmat[i][j] == 1){ cout << 0; return 0; }
                dirmat[j][i] = 1;
            }
        }
    }

    // Check contradictions
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j && dirmat[i][j] && dirmat[j][i]){
                cout << 0;
                return 0;
            }
        }
    }

    // Build A chain (Lmin:0, Lmax:1), B chain (Rmin:2, Rmax:3)
    vector<int> A, B;
    for(int i=1;i<=n;i++){
        if(op[i] <= 1) A.push_back(i);
        else B.push_back(i);
    }
    int p = A.size(), q = B.size();

    // Precompute limits
    vector<int> limitA(p+1), limitB(q+1);

    // limitA[k]: for A[k], max B-prefix allowed
    for(int k=1; k<=p; k++){
        int pos = A[k-1];
        int t0 = q+1;
        for(int t=1; t<=q; t++){
            if(dirmat[pos][ B[t-1] ] == 1){
                t0 = t;
                break;
            }
        }
        limitA[k] = t0 - 1;
    }

    // limitB[k]: for B[k], max A-prefix allowed
    for(int k=1; k<=q; k++){
        int pos = B[k-1];
        int t0 = p+1;
        for(int t=1; t<=p; t++){
            if(dirmat[pos][ A[t-1] ] == 1){
                t0 = t;
                break;
            }
        }
        limitB[k] = t0 - 1;
    }

    // DP f(i,j)
    // f[i][j] = ways after placing values 1..i, using j from A-chain
    dp[0][0] = 1;

    for(int i=0;i<n;i++){
        int jlo = max(0, i - q);
        int jhi = min(i, p);
        for(int j=jlo; j<=jhi; j++){
            long long cur = dp[i][j];
            if(!cur) continue;

            int usedA = j;
            int usedB = i - j;

            // take from A → A[usedA+1]
            if(usedA < p){
                if(usedB <= limitA[usedA+1]){
                    dp[i+1][usedA+1] = (dp[i+1][usedA+1] + cur) % MOD;
                }
            }
            // take from B → B[usedB+1]
            if(usedB < q){
                if(usedA <= limitB[usedB+1]){
                    dp[i+1][usedA] = (dp[i+1][usedA] + cur) % MOD;
                }
            }
        }
    }

    cout << dp[n][p] % MOD;
    return 0;
}
