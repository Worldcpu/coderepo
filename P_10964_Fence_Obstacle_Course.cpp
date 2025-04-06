#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define getn(x) (x + 100001) // 坐标偏移，将负坐标转换为正数方便处理
using namespace std;
constexpr int MN = 2e6 + 15;
int f[MN][2], lc[MN], rc[MN], n, s;
// lc，rc为记录的编号
struct zhalan {
    int l, r;
} zl[MN];

struct segtree {
    int l, r, val, cov;
} t[MN << 2];


void pushdown(int p) {
    if (t[p].cov) {
        t[ls].val = t[rs].val = t[ls].cov = t[rs].cov = t[p].cov;
        t[p].cov = 0;
    }
}

void build(int p, int l, int r) {
    t[p].l = l;
    t[p].r = r;
    if (l == r) return;
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
}

void cover(int p, int fl, int fr, int k) {
    if (t[p].l >= fl && t[p].r <= fr) {
        t[p].cov = t[p].val = k;
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (mid >= fl) cover(ls, fl, fr, k);
    if (mid < fr) cover(rs, fl, fr, k);
}


int query(int p, int pos) {
    if (t[p].l == t[p].r) return t[p].val;
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    return pos <= mid ? query(ls, pos) : query(rs, pos);
}

int main() {
    memset(f, 0x3f, sizeof(f)); // 初始化为极大值
    build(1, 1, 2e6);
    zl[0].l = zl[0].r = getn(0); //注意这里是getn(0)! 原点也要偏移！
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        zl[i].l = getn(a);//偏移l，r
        zl[i].r = getn(b);
        lc[i] = query(1, zl[i].l); // 查询当前平台i的左端点下方第一个平台编号
        rc[i] = query(1, zl[i].r); // 查询当前平台i的右端点下方第一个平台编号
        cover(1, zl[i].l, zl[i].r, i); // 将区间[zl[i].l, zl[i].r]标记为平台i
    }

    f[n][0] = abs(getn(s) - zl[n].l);
    f[n][1] = abs(zl[n].r - getn(s));

    for (int i = n; i >= 1; i--) {// 递推，启动！
        // 从当前平台i的左端点跳到下方平台lc[i]的左右端点
        f[lc[i]][0] = min(f[lc[i]][0], f[i][0] + abs(zl[i].l - zl[lc[i]].l));
        f[lc[i]][1] = min(f[lc[i]][1], f[i][0] + abs(zl[i].l - zl[lc[i]].r));
        // 从当前平台i的右端点跳到下方平台rc[i]的左右端点
        f[rc[i]][0] = min(f[rc[i]][0], f[i][1] + abs(zl[i].r - zl[rc[i]].l));
        f[rc[i]][1] = min(f[rc[i]][1], f[i][1] + abs(zl[i].r - zl[rc[i]].r));
    }
    cout << f[0][0]; // 这里也可以是f[0][1]，左端点和右端点是重合的
    return 0;
}
