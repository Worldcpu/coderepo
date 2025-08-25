#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int MAXN = 1e6 + 6, mod = 998244353;
int fac[MAXN], inv[MAXN];
int qpow(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        a[i] = s[i - 1] - '(';
    vector<int> suml(n + 1), sumr(n + 1), st;
    vector<int> pos;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 0)
        {
            st.push_back(i);
            if (st.size() == 1)
                pos.push_back(i);
        }
        else
        {
            st.pop_back();
            if (st.size() == 1 || st.size() == 0)
                pos.push_back(i);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        suml[i] = suml[i - 1];
        sumr[i] = sumr[i - 1];
        if (!a[i])
            suml[i]++;
        else
            sumr[i]++;
    }
    int ans = 0;
    for (int i = 0; i < pos.size(); i++)
    {
        int pre = qpow(2, suml[pos[i]]);
        int suf = qpow(2, sumr[n] - sumr[pos[i]]);
        int tmp = pre * suf % mod;
        ans = (ans + tmp) % mod;
        if (i != pos.size() - 1)
        {
            suf = qpow(2, sumr[n] - sumr[pos[i + 1]]);
            tmp = pre * suf % mod;
            ans = (ans - tmp + mod) % mod;
        }
    }
    ans = ans * qpow(qpow(2, n), mod - 2) % mod;
    cout << ans << endl;
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    while (t--)
        solve();
    return 0;
}