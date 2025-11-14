#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 5e5 + 10;

int n, T, answer;
int a[MAX_N];

int readInt() {
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

void maximize(int &x, int y) {
    x = max(x, y);
}

int distance(int x, int y) {
    return min(abs(x - y), T - abs(x - y));
}

int main() {
    n = readInt();
    T = readInt();
    for (int i = 1; i <= n; i++)
        a[i] = readInt(), a[i] %= T;
    sort(a + 1, a + n + 1);
    for (int i = 1; i < n; i++) 
        maximize(answer, a[i + 1] - a[i]);
    maximize(answer, a[1] + T - a[n]);
    if (T == answer)
        cout << "0" << endl;
    else
        cout << (T - answer - 1) / 2 + 1 << endl;
    return 0;
}
