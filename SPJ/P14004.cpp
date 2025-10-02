#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

extern int plan_vacation(int N, vector<int> L, vector<int> R, long long K);

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int N = inf.readInt();
    long long K = inf.readLong();
    vector<int> L(N), R(N);
    for(int i=0;i<N;i++){
        L[i] = inf.readInt();
        R[i] = inf.readInt();
    }

    int ans = plan_vacation(N, L, R, K);

    int pans = ouf.readInt();
    if(pans != ans){
        quitf(_wa, "Wrong answer: expected %d, found %d", ans, pans);
    }
    quitf(_ok, "Correct: %d", ans);
}
