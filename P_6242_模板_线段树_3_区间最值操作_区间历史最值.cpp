#include <bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
#define ll long long
using namespace std;
constexpr int MN = 5e6 + 15, NINF = -2e9;
template <typename type>
inline void read(type &x)
{
    x = 0;
    bool flag(0);
    char ch = getchar();
    while (!isdigit(ch))
        flag = ch == '-', ch = getchar();
    while (isdigit(ch))
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    flag ? x = -x : 0;
}
int n, m;
struct segtree
{
    ll sum;
    int l, r, maxa, maxb, se, mxcnt;
    int add1, add2, mxadd1, mxadd2;
} t[MN << 2];

void pushup(int p)
{
    t[p].sum = t[ls].sum + t[rs].sum;
    t[p].maxa = max(t[ls].maxa, t[rs].maxa);
    t[p].maxb = max(t[ls].maxb, t[rs].maxb);

    if (t[ls].maxa == t[rs].maxa)
    {
        t[p].se = max(t[ls].se, t[rs].se);
        t[p].mxcnt = t[ls].mxcnt + t[rs].mxcnt;
    }
    else if (t[ls].maxa > t[rs].maxa)
    {
        t[p].se = max(t[ls].se, t[rs].maxa);
        t[p].mxcnt = t[ls].mxcnt;
    }
    else
    {
        t[p].se = max(t[ls].maxa, t[rs].se);
        t[p].mxcnt = t[rs].mxcnt;
    }
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if (l == r)
    {
        read(t[p].maxa);
        t[p].sum = t[p].maxb = t[p].maxa;
        t[p].se = NINF;
        t[p].mxcnt = 1;
        return;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(p);
}

void doit(int k1, int k2, int k3, int k4, int p)
{
    // 更新历史最大值
    t[p].maxb = max(t[p].maxb, t[p].maxa + k3);
    // 更新当前最大值
    t[p].maxa += k1;
    // 更新区间和
    t[p].sum += 1ll * k1 * t[p].mxcnt + 1ll * k2 * (t[p].r - t[p].l + 1 - t[p].mxcnt);
    // 更新次大值
    if (t[p].se != NINF)
        t[p].se += k2;
    // 更新标记
    t[p].mxadd1 = max(t[p].mxadd1, t[p].add1 + k3);
    t[p].mxadd2 = max(t[p].mxadd2, t[p].add2 + k4);
    t[p].add1 += k1;
    t[p].add2 += k2;
}

void pushdown(int p)
{
    int maxn = max(t[ls].maxa, t[rs].maxa);
    if (t[ls].maxa == maxn)
    {
        doit(t[p].add1, t[p].add2, t[p].mxadd1, t[p].mxadd2, ls);
    }
    else
    {
        doit(t[p].add2, t[p].add2, t[p].mxadd2, t[p].mxadd2, ls);
    }
    if (t[rs].maxa == maxn)
    {
        doit(t[p].add1, t[p].add2, t[p].mxadd1, t[p].mxadd2, rs);
    }
    else
    {
        doit(t[p].add2, t[p].add2, t[p].mxadd2, t[p].mxadd2, rs);
    }
    t[p].add1 = t[p].add2 = t[p].mxadd1 = t[p].mxadd2 = 0;
}

void updateadd(int p, int fl, int fr, ll k)
{
    if (t[p].l >= fl && t[p].r <= fr)
    {
        t[p].sum += 1ll * k * (t[p].r - t[p].l + 1);
        t[p].maxa += k;
        t[p].maxb = max(t[p].maxb, t[p].maxa);
        if (t[p].se != NINF)
            t[p].se += k;
        t[p].add1 += k;
        t[p].add2 += k;
        t[p].mxadd1 = max(t[p].mxadd1, t[p].add1);
        t[p].mxadd2 = max(t[p].mxadd2, t[p].add2);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if (mid >= fl)
        updateadd(ls, fl, fr, k);
    if (mid < fr)
        updateadd(rs, fl, fr, k);
    pushup(p);
}

void updatemin(int p, int fl, int fr, int v)
{
    if (v >= t[p].maxa || t[p].l > fr || t[p].r < fl)
        return;
    if (t[p].l >= fl && t[p].r <= fr && v > t[p].se)
    {
        int k = t[p].maxa - v;
        t[p].sum -= 1ll * k * t[p].mxcnt;
        t[p].maxa = v;
        t[p].maxb = max(t[p].maxb, v); // 更新历史最大值
        t[p].add1 -= k;
        return;
    }
    pushdown(p);
    updatemin(ls, fl, fr, v);
    updatemin(rs, fl, fr, v);
    pushup(p);
}

ll querysum(int p, int fl, int fr)
{
    if (t[p].l >= fl && t[p].r <= fr)
    {
        return t[p].sum;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    ll res = 0;
    if (mid >= fl)
        res += querysum(ls, fl, fr);
    if (mid < fr)
        res += querysum(rs, fl, fr);
    return res;
}

int querymaxa(int p, int fl, int fr)
{
    if (t[p].l >= fl && t[p].r <= fr)
    {
        return t[p].maxa;
    }
    pushdown(p);
    int res = NINF;
    int mid = t[p].l + t[p].r >> 1;
    if (mid >= fl)
        res = querymaxa(ls, fl, fr);
    if (mid < fr)
        res = max(res, querymaxa(rs, fl, fr));
    return res;
}

int querymaxb(int p, int fl, int fr)
{
    if (t[p].l >= fl && t[p].r <= fr)
    {
        return t[p].maxb;
    }
    pushdown(p);
    int res = NINF;
    int mid = t[p].l + t[p].r >> 1;
    if (mid >= fl)
        res = querymaxb(ls, fl, fr);
    if (mid < fr)
        res = max(res, querymaxb(rs, fl, fr));
    return res;
}

int main()
{
    read(n);
    read(m);
    build(1, 1, n);
    int op, x, y, z;
    while (m--)
    {
        read(op);
        read(x);
        read(y);
        if (op == 1)
        {
            read(z);
            updateadd(1, x, y, z);
        }
        else if (op == 2)
        {
            read(z);
            updatemin(1, x, y, z);
        }
        else if (op == 3)
        {
            cout << querysum(1, x, y) << '\n';
        }
        else if (op == 4)
        {
            cout << querymaxa(1, x, y) << '\n';
        }
        else if (op == 5)
        {
            cout << querymaxb(1, x, y) << '\n';
        }
    }
    return 0;
}