#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MN = 1e5 + 15;
int n, k, pre[2500][MN];
ll f[2][MN], s[MN], q[MN], l, r;

// 以防忘转移方程，先写一下,f(i,j)表示划分了i段，进行到第j个数
// f(i,j)=f(i-1,k)+s[k]*(s[j]-s[k])
//       =f(i-1,k)+s[k]*s[j]-s[k]*s[k]

ll getn(ll x)// 奇偶判断，滚动专属
{
    return x & 1;
}

long double getk(int i, int x, int y)
{
    if (s[x] == s[y])//SIGFPE中的除以0
        return -1e18;
    return 1.0 * 
    ((f[getn(i - 1)][x] - s[x] * s[x]) - (f[getn(i - 1)][y] - s[y] * s[y])) 
    / (s[y] - s[x]);
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        s[i] = s[i - 1] + x;
    }
    for (int i = 1; i <= k; i++)
    {
        l = 1, r = 0;
        q[++r] = 0;
        for (int j = 1; j <= n; j++)
        {
            while (l < r && getk(i, q[l], q[l + 1]) <= s[j])
            {
                l++;
            }
            f[getn(i)][j] = f[getn(i - 1)][q[l]] + s[q[l]] * s[j] - s[q[l]] * s[q[l]];
            pre[i][j] = q[l];
            while (l < r && getk(i, q[r - 1], q[r]) >= getk(i, q[r], j))
            {
                r--;
            }
            q[++r] = j;
        }
    }
    cout << f[(k & 1)][n] << '\n';
    for (int i = k, j = n; i >= 1; i--)
    {
        j = pre[i][j];
        cout << j << " ";
    }
    return 0;
}