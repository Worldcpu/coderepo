#include <bits/stdc++.h>
using namespace std;
random_device rd;

string generate_brackets(int n) {
    string res;
    int open = 1, close = 0; // 第一个 '(' 已经放
    res += '(';

    for(int i = 1; i < n; ++i) {
        if(open < n / 2 && (close == open || rand() % 2)) {
            res += '(';
            open++;
        } else {
            res += ')';
            close++;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    freopen("dp.in","w",stdout);
    srand(rd());
    int n=1e6;
    string s = generate_brackets(n);
    cout << s << endl;
}
