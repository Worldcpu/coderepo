#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN = 3e5+15;
int n, s;
ll a[MN], sumt[MN], sumc[MN], f[MN], q[MN];
int main()
{
    cin >> n >> s;
    for (int i = 1; i <= n; i++)
    {
        ll t, c;
        cin >> t >> c;
        sumt[i] = sumt[i - 1] + t;
        sumc[i] = sumc[i - 1] + c;
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;

    // O(n^2)
    // for(int i=1;i<=n;i++){
    //     for(int j=0;j<i;j++){
    //         f[i]=min(f[i],f[j]+sumt[i]*(sumc[i]-sumc[j])+s*(sumc[n]-sumc[j]));
    //     }
    // }

    // O(n)
    int l = 1, r = 0;
    q[++r]=0;

    for (int i = 1; i <= n; i++)
    {
        ll k=s+sumt[i];
        //为什么这里是l<r? l<r 能保证队列中至少有2个数，我们比较斜率是 delta(y)/delta(x) 2个值凑delta
        while (l < r && (f[q[l + 1]] - f[q[l]]) <= k * (sumc[q[l + 1]] - sumc[q[l]]))
        {
            // 除法转乘法避免小数
            l++;
        }
        f[i] = f[q[l]] - k * sumc[q[l]] + sumt[i] * sumc[i] + s * sumc[n];
        while (l < r && (f[q[r]] - f[q[r - 1]]) * (sumc[i] - sumc[q[r]]) >= (f[i] - f[q[r]]) * (sumc[q[r]] - sumc[q[r - 1]]))
            r--;
        // 分式交叉相乘避免小数
        q[++r] = i;
    }
    cout << f[n];
    return 0;
}