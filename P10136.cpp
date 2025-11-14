#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 15;            // 序列长度
    vector<int> lb(n + 1); // lb数组，1-indexed

    for (int i = 1; i <= n; ++i) {
        int p = i - 1, q = 0;
        if (p) q = lb[p];
        if (!p || p - q != q - (q ? lb[q] : 0))
            lb[i] = i - 1;
        else
            lb[i] = lb[q];
    }

    // 输出
    for (int i = 1; i <= n; ++i)
        cout << "i=" << i << ", lb[i]=" << lb[i] << '\n';
}
