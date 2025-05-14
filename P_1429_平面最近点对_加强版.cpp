#include <bits/stdc++.h>
#define DBL_MAX 1e18
using namespace std;

constexpr int MN = 200005;
struct Node {
    int x, y, d; // d: 分割维度（0 表示 x，1 表示 y）
};
Node a[MN];

int lc[MN], rc[MN], lx[MN], rx[MN], ly[MN], ry[MN], id[MN], rt, n,nowd;
double ans, px, py, fx, fy;

// 计算两点之间的平方距离
double getdis(int x, int y) {
    long long dx = a[x].x - a[y].x;
    long long dy = a[x].y - a[y].y;
    return dx * dx + dy * dy;
}

// 比较函数，按 x 维度排序
bool cmpx(int x, int y) {
    return a[x].x < a[y].x;
}

// 比较函数，按 y 维度排序
bool cmpy(int x, int y) {
    return a[x].y < a[y].y;
}

// 更新当前节点的区域极值
void pushup(int x) {
    lx[x] = rx[x] = a[x].x;
    ly[x] = ry[x] = a[x].y;
    if (lc[x]) {
        lx[x] = min(lx[x], lx[lc[x]]);
        rx[x] = max(rx[x], rx[lc[x]]);
        ly[x] = min(ly[x], ly[lc[x]]);
        ry[x] = max(ry[x], ry[lc[x]]);
    }
    if (rc[x]) {
        lx[x] = min(lx[x], lx[rc[x]]);
        rx[x] = max(rx[x], rx[rc[x]]);
        ly[x] = min(ly[x], ly[rc[x]]);
        ry[x] = max(ry[x], ry[rc[x]]);
    }
}

// 构建 K-D Tree
int build(int l, int r, int dim) {
    if (r < l) return 0;
    int mid = (l + r) >> 1;
    px = py = fx = fy = 0;
    for (int i = l; i <= r; ++i) {
        px += a[id[i]].x;
        py += a[id[i]].y;
    }
    px /= (r - l + 1);
    py /= (r - l + 1);
    for (int i = l; i <= r; ++i) {
        fx += (a[id[i]].x - px) * (a[id[i]].x - px);
        fy += (a[id[i]].y - py) * (a[id[i]].y - py);
    }
    if (fx < fy) {
        nth_element(id + l, id + mid, id + r + 1, cmpx);
    } else {
        nth_element(id + l, id + mid, id + r + 1, cmpy);
    }
    int x = id[mid];
    a[x].d = dim; // 当前节点分割维度
    lc[x] = build(l, mid - 1, 1 - dim);
    rc[x] = build(mid + 1, r, 1 - dim);
    pushup(x);
    return x;
}

// 计算当前节点的子区域到查询点的距离下界
double fac(int x) {
    if (!x) return DBL_MAX;
    double ret = 0, tmp = 0;
    if (lx[x] > a[nowd].x) tmp += lx[x] - a[nowd].x;
    if (rx[x] < a[nowd].x) tmp += a[nowd].x - rx[x];
    ret += tmp * tmp;
    tmp = 0;
    if (ly[x] > a[nowd].y) tmp += ly[x] - a[nowd].y;
    if (ry[x] < a[nowd].y) tmp += a[nowd].y - ry[x];
    ret += tmp * tmp;
    return ret;
}

// 查询最近邻
void query(int x) {
    if (!x) return;
    ans = min(ans, getdis(x, nowd));
    double fl = fac(lc[x]), fr = fac(rc[x]);
    if (fl < fr) {
        if (fl < ans) query(lc[x]);
        if (fr < ans) query(rc[x]);
    } else {
        if (fr < ans) query(rc[x]);
        if (fl < ans) query(lc[x]);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        id[i] = i;
        cin >> a[i].x >> a[i].y;
    }
    rt = build(1, n, 0); // 初始分割维度为 x
    ans = DBL_MAX;

    for (int i = 1; i <= n; ++i) {
        nowd = id[i];
        query(rt);
    }

    cout << fixed << setprecision(2) << sqrt(ans) << endl;
    return 0;
}