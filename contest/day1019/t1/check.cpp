#include "../../testlib.h"
#include <vector>
#include <iostream>

using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int n, m;

void readAns(InStream &ouf) {
    vector<vector<int>> table(n, vector<int>(m));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            table[i][j] = ouf.readInt(0, 4, "t");
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value = table[i][j];
            int count = 0;
            
            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    if (table[ni][nj] == value) {
                        count++;
                    }
                }
            }
            
            if (count != value) {
                ouf.quitf(_wa, "Cell (%d, %d) with value %d has %d matching neighbors", i+1, j+1, value, count);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    m = inf.readInt();
    
    readAns(ans);
    readAns(ouf);
    
    quitf(_ok, "Valid output");
}
