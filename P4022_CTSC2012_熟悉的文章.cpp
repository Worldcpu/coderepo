#include <bits/stdc++.h>
using namespace std;
constexpr int MN = 5e5 + 15;
int n, m, len, f[MN], ql, qr, q[MN], L[MN];

struct SAM {
    int nxt[MN][3], fa[MN], cnt[MN], len[MN], cnt_init[MN], tot, lst;

    void init() {
        tot = lst = 0;
        fa[0] = -1;
        len[0] = 0;
        memset(nxt[0], 0, sizeof(nxt[0]));
        cnt_init[0] = 0;
    }

    void find(string s, int slen) {
        int p = 0, now = 0;
        for (int i = 0; i < slen; i++) {
            int x = s[i] - '0';
            if (x < 0 || x > 1) continue;
            if (nxt[p][x]) {
                now++;
                p = nxt[p][x];
            } else {
                for (; p != -1 && !nxt[p][x]; p = fa[p]);
                if (p == -1) p = 0, now = 0;
                else now = len[p] + 1, p = nxt[p][x];
            }
            L[i + 1] = now;
        }
    }

    void extend(int c) {
        int cur = ++tot;
        len[cur] = len[lst] + 1;
        cnt_init[cur] = 1;
        memset(nxt[cur], 0, sizeof(nxt[cur]));
        int p = lst;
        while (p != -1 && !nxt[p][c]) {
            nxt[p][c] = cur;
            p = fa[p];
        }
        if (p == -1) {
            fa[cur] = 0;
        } else {
            int q = nxt[p][c];
            if (len[q] == len[p] + 1) {
                fa[cur] = q;
            } else {
                int nq = ++tot;
                len[nq] = len[p] + 1;
                memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
                fa[nq] = fa[q];
                cnt_init[nq] = 0;
                while (p != -1 && nxt[p][c] == q) {
                    nxt[p][c] = nq;
                    p = fa[p];
                }
                fa[q] = fa[cur] = nq;
            }
        }
        lst = cur;
    }
} sam;

bool check(int mid) {
    int ql = 0, qr = -1;
    for (int i = 0; i <= mid - 1; i++) f[i] = 0;
    for (int i = mid; i <= len; i++) {
        f[i] = f[i - 1];
        while (ql <= qr && (f[i - mid] - (i - mid)) > (f[q[qr]] - q[qr])) qr--;
        q[++qr] = i - mid;
        while (ql <= qr && q[ql] < (i - L[i])) ql++;
        if (ql <= qr) f[i] = max(f[i], f[q[ql]] - q[ql] + i);
    }
    return f[len] * 10 >= len * 9;
}

int main() {
    cin >> n >> m;
    sam.init();
    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        for (auto c : s) {
            sam.extend(c - '0');
        }
        sam.extend(2); 
    }

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        len = s.length();
        sam.find(s, len);
        int l = 1, r = len+1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        cout << l << '\n';
    }

    return 0;
}
