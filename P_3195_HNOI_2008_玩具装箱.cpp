#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MN = 5e4 + 15;

ll n, ql, L, qr, f[MN], s[MN];
struct node
{
    ll c, l, r;
} q[MN];

// https://www.latexlive.com/#JTdCJTVDc21hbGwlMjBmJTVCaSU1RD0lNUNtaW4lNUNsaW1pdHNfJTdCaj0xJTdEJTVFJTdCaS0xJTdEJTIwZiU1QmolNUQrKHMlNUJpJTVELXMlNUJqJTVEK2ktai0xLUwpJTVFMiUyMCU1Q3F1YWQlMjAlNUN0ZXh0JTdCJUU1JTg1JUI2JUU0JUI4JUFEcyVFNCVCOCVCQSU3RENfaSU1Q3RleHQlN0IlRTUlODklOEQlRTclQkMlODAlRTUlOTIlOEMlRUYlQkMlOEMlRTUlOTAlOEUlRTklOUQlQTIlRTklODIlQTMlRTQlQjglODAlRTYlODklOTglRTYlOTglQUYlN0QlN0R2YWwoaisxLGkpJTVFMiUyMCUyMA==

ll val(int j, int i)
{
    ll right = (s[i] - s[j] + i - j - 1 - L);
    return f[j] + right * right;
}

void insert(int x)
{
    int pos = n + 1;
    while (ql <= qr && val(x, q[qr].l) <= val(q[qr].c, q[qr].l))
    {
        pos = q[qr--].l;
    }
    if (ql <= qr && val(x, q[qr].r) <= val(q[qr].c, q[qr].r))
    {
        int l = q[qr].l, r = q[qr].r;
        while (l + 1 < r)
        {
            int mid = l + r >> 1;
            if (val(x, mid) <= val(q[qr].c, mid))
                r = mid;
            else
                l = mid;
        }
        q[qr].r = r - 1;
        pos = r;
    }
    if (pos != n + 1)
    {
        q[++qr] = {x, pos, n};
    }
}

int main()
{
    cin >> n >> L;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    ql = 1, qr = 0;
    q[++qr] = {0, 1, n};
    for (int i = 1; i <= n; i++)
    {
        while (ql <= qr && q[ql].r == i - 1)
            ql++;
        q[ql].l = i;
        f[i] = val(q[ql].c, i);
        // if(q[ql].r==i) ql++;
        // q[ql].l=i+1;
        insert(i);
    }
    cout << f[n];
    return 0;
}