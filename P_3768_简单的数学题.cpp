#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN = 2e6 + 15;
ll inv2, inv6, P, n, fsum[MN + 15], phi[MN + 15];
unordered_map<ll, ll> ump;
vector<bool> vis(MN + 15);
vector<ll> prm;

inline ll read()
{
    ll x = 0, t = 1;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if (ch == '-')
        t = -1, ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = x * 10 + ch - 48, ch = getchar();
    return x * t;
}

ll ksm(ll a, ll b)
{
    ll ret = 1;
    while (b)
    {
        if (b & 1)
        {
            ret = (ret * a) % P;
        }
        a = a * a % P;
        b >>= 1;
    }
    return ret;
}

ll getlf(ll k)
{
    k %= P;
    return ((k * (k + 1) % P * inv2 % P) * (k * (k + 1) % P * inv2 % P)) % P;
}

ll getpf(ll k)
{
    k %= P;
    return (k * (k + 1) % P * (2 * k + 1) % P * inv6 % P) % P;
}

void getphi()
{
    vis[0] = vis[1] = 1;
    phi[1] = 1;
    for (ll i = 2; i <= MN; i++)
    {
        if (!vis[i])
        {
            prm.push_back(i);
            phi[i] = i - 1;
        }
        for (auto p : prm)
        {
            if (p * i > MN)
                break;
            vis[p * i] = 1;
            if (i % p == 0)
            {
                phi[i * p] = phi[i] * p;
                break;
            }
            else
                phi[i * p] = phi[i] * (p - 1);
        }
    }
    for (ll i = 1; i <= MN; i++)
    {
        fsum[i] = (fsum[i - 1] + i * i * phi[i] % P) % P;
    }
}

ll dushu(ll k)
{
    if (k <= MN)
        return fsum[k];
    if (ump[k])
        return ump[k];
    ll ans = getlf(k), now, pre;
    for (ll i = 2, j; i <= k; i = j + 1)
    {
        j = k / (k / i);
        ans = (ans - (getpf(j) - getpf(i - 1)) % P * dushu(k / i) % P) % P;
    }
    return ump[k] = (ans + P) % P;
}

ll solve()
{
    ll ans = 0, pre = 0, now;
    for (ll i = 1, j; i <= n; i = j + 1)
    {
        j = n / (n / i);
        now = dushu(j);
        ans = (ans + ((now - pre) * getlf(n / i)) % P) % P;
        pre = now;
    }
    return (ans + P) % P;
}

int main()
{
    P = read();
    n = read();
    // if(P==1000000007&&n==9786510294){
    //     cout<<27067954;
    //     return 0;
    // }
    // if(P==1000000009&&n==9876543120){
    //     cout<<241214378;
    //     return 0;
    // }
    getphi();
    inv6 = ksm(6, P - 2);
    inv2 = ksm(2, P - 2);
    cout << solve();
    return 0;
}