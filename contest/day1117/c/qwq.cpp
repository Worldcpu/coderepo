#include <bits/stdc++.h>
using namespace std;

int n;
int ans = 0;
vector<int> perm;
vector<bool> used;

void dfs(int pos) {
    if (pos == n) {
        ans++;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            if (pos == 0 || abs(perm[pos - 1] - i) > 1) {
                used[i] = true;
                perm[pos] = i;
                dfs(pos + 1);
                used[i] = false;
            }
        }
    }
}

int main() {
    cout << "n? ";
    cin >> n;
    perm.resize(n);
    used.assign(n + 1, false);
    dfs(0);
    cout << "Number of valid permutations: " << ans << endl;
    return 0;
}
