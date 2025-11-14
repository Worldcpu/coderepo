#include <bits/stdc++.h>
using namespace std;
constexpr int MN = 5e5 + 15;
int n, cntd1, cntd2, ans, s[2][MN], t[2][MN], cnt[2][2][MN], pos[2][MN], it[2];

void init()
{
    for (int i = 1; i <= cntd1; i++)
    {
        cnt[0][0][i] = 0;
        cnt[0][1][i] = 0;
    }
    for (int i = 1; i <= cntd2; i++)
    {
        cnt[1][0][i] = 0;
        cnt[1][1][i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        pos[0][i] = pos[1][i] = 0;
    }
    cntd1 = cntd2 = 1;
    it[0] = it[1] = 0;
}

void solve()
{
    cin >> n;
    init();
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char x;
            cin >> x;
            s[i][j] = x - '0';
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char x;
            cin >> x;
            t[i][j] = x - '0';
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (t[0][i])
            cnt[0][s[0][i]][cntd1]++;
        else
            pos[0][cntd1++] = i;

        if (t[1][i])
            cnt[1][s[1][i]][cntd2]++;
        else
            pos[1][cntd2++] = i;
    }
    pos[0][cntd1] = pos[1][cntd2] = n+1;

    ans = n;
    while (it[0] < cntd1 || it[1] < cntd2)
    {
        if (pos[0][it[0]] == pos[1][it[1]])
        {
            it[0]++, it[1]++;
        }
        else if (pos[0][it[0]] > pos[1][it[1]])
            it[1]++;
        else
            it[0]++;
        int now = (pos[0][it[0]] <= pos[1][it[1]]);
        int siz = cnt[now ^ 1][0][it[now ^ 1]] + cnt[now ^ 1][1][it[now ^ 1]];
        if (cnt[now ^ 1][0][it[now ^ 1]] > cnt[now][0][it[now]])
        {
            ans -= cnt[now ^ 1][0][it[now ^ 1]] - cnt[now][0][it[now]];
            cnt[now][1][it[now]] -= siz - cnt[now][0][it[now]];
            cnt[now ^ 1][0][it[now ^ 1]] = cnt[now ^ 1][1][it[now ^ 1]] = cnt[now][0][it[now]] = 0;
        }
        else if (cnt[now ^ 1][1][it[now ^ 1]] > cnt[now][1][it[now]])
        {
            ans -= cnt[now ^ 1][1][it[now ^ 1]] - cnt[now][1][it[now]];
            cnt[now][0][it[now]] -= siz - cnt[now][1][it[now]];
            cnt[now ^ 1][0][it[now ^ 1]] = cnt[now ^ 1][1][it[now ^ 1]] = cnt[now][1][it[now]] = 0;
        }
        else
        {
            cnt[now][0][it[now]] -= cnt[now ^ 1][0][it[now ^ 1]];
            cnt[now][1][it[now]] -= cnt[now ^ 1][1][it[now ^ 1]];
            cnt[now ^ 1][0][it[now ^ 1]] = cnt[now ^ 1][1][it[now ^ 1]] = 0;
        }
        if (it[0] == cntd1 && it[1] == cntd2)
            break;
        if (pos[now][it[now]] == pos[now ^ 1][it[now ^ 1]])
            ans -= s[now][pos[now][it[now]]] != s[now ^ 1][pos[now][it[now]]];
        else if (cnt[now][s[now ^ 1][pos[now ^ 1][it[now ^ 1]]]][it[now]])
            cnt[now][s[now ^ 1][pos[now ^ 1][it[now ^ 1]]]][it[now]]--;
        else
            ans--, cnt[now][!s[now ^ 1][pos[now ^ 1][it[now ^ 1]]]][it[now]]--;
    }
    cout<<ans<<'\n';
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}