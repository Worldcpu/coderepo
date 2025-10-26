// compile: g++ -O2 gen_hack.cpp -o gen_hack
// run: ./gen_hack > hack_input.txt

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k = 316; // sqrt-like
    int n = k * k; // 99856
    int target_n = 100000;
    int pad = target_n - n; // 144
    // build array: for val = 1..k, push k copies
    vector<int> a;
    a.reserve(target_n);
    for (int val = 1; val <= k; ++val) {
        for (int t = 0; t < k; ++t) a.push_back(val);
    }
    // pad with value 1 to reach exactly target_n
    for (int i = 0; i < pad; ++i) a.push_back(1);

    // queries: all ordered pairs (x,y) with 1 <= x,y <= k and x != y
    vector<pair<int,int>> queries;
    queries.reserve(k * (k - 1));
    for (int x = 1; x <= k; ++x) {
        for (int y = 1; y <= k; ++y) {
            if (x == y) continue;
            queries.emplace_back(x, y);
        }
    }

    int q = (int)queries.size();
    cout << (int)a.size() << ' ' << q << '\n';
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    for (auto &pr : queries) {
        cout << pr.first << ' ' << pr.second << '\n';
    }
    return 0;
}
