#include <bits/stdc++.h>
#define ll long long
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int MN = 1e6 + 15;
const ll INF = -1e17;
struct segtree
{
    int l, r;
    ll mx, cov, add;
    bool iscov;
} t[MN << 2];

int n, m;

void pushup(int p)
{
    t[p].mx = max(t[ls].mx, t[rs].mx);
}

void pushdown(int p)
{
    if (t[p].iscov)
    {
        t[ls].mx = t[rs].mx = t[ls].cov = t[rs].cov = t[p].cov;
        t[ls].add = t[rs].add = t[p].add;
        t[ls].mx += t[p].add;
        t[rs].mx += t[p].add;
        t[ls].iscov = t[rs].iscov = 1;
        // t[p].iscov=t[p].cov=t[p].add=0;
    }
    else
    {
        t[ls].mx += t[p].add;
        t[rs].mx += t[p].add;
        t[ls].add += t[p].add;
        t[rs].add += t[p].add;
        // t[p].add=t[p].cov=0;
    }
    t[p].iscov = t[p].cov = t[p].add = 0;
}

ll a[MN];

void build(int p, int l, int r)
{
    t[p].l = l;
    t[p].r = r;
    t[p].mx = INF;
    if (l == r)
    {
        t[p].mx = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(p);
}

void update1(int p, int fl, int fr, ll k)
{
    if (t[p].l >= fl && t[p].r <= fr)
    {
        t[p].mx = t[p].cov = k;
        t[p].add = 0;
        t[p].iscov = 1;
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (mid >= fl)
        update1(ls, fl, fr, k);
    if (mid < fr)
        update1(rs, fl, fr, k);
    pushup(p);
}

void update2(int p, int fl, int fr, ll k)
{
    if (t[p].l >= fl && t[p].r <= fr)
    {
        t[p].add += k;
        t[p].mx += k;
        return;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    if (mid >= fl)
        update2(ls, fl, fr, k);
    if (mid < fr)
        update2(rs, fl, fr, k);
    pushup(p);
}

ll query(int p, int fl, int fr)
{
    if (t[p].l >= fl && t[p].r <= fr)
    {
        return t[p].mx;
    }
    pushdown(p);
    int mid = (t[p].l + t[p].r) >> 1;
    ll ret = INF;
    if (mid >= fl)
        ret = query(ls, fl, fr);
    if (mid < fr)
        ret = max(ret, query(rs, fl, fr));
    return ret;
}

int main()
{
    //freopen("ans.in","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    ll op, x, y, z;
    build(1, 1, n);
    while (m--)
    {
        /* code */
        cin >> op >> x >> y;
        if (op == 1)
        {
            cin >> z;
            update1(1, x, y, z);
        }
        if (op == 2)
        {
            cin >> z;
            update2(1, x, y, z);
        }
        if (op == 3)
        {
            cout << query(1, x, y) << '\n';
        }
    }

    return 0;
}