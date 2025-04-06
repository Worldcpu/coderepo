#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 155;
const int maxm = 11;
int a[maxn][maxm];
int T, n, m, k;
int f[2][60005];
int pow[11];
void init()
{
	pow[0] = 1;
	for (int i = 1; i <= 10; i++)
		pow[i] = pow[i - 1] * 3;
}
int suan(int x, int pos)
{ // 数 x 的三进制第 pos 位是多少
	return x % pow[pos] / pow[pos - 1];
}
bool ifok(int x, int pos, int lst)
{ // 第 x 行第 pos 位是否能放
	if (!a[x][pos] && !suan(lst, m - pos + 1))
		return 1; // 当前位置不能损坏，上一行当前位置必须为零
	return 0;
}
void dfs(int x /*这是第几行*/, int lst /*上一行的状态*/, int now /*当前行搜索到的状态*/, int pos /*从左往右搜到第三进制几位*/, int cnt /*放了几个数了*/)
{
	if (!pos)
	{ // 更新状态
		f[x % 2][now] = max(f[x % 2][now], f[(x - 1) % 2][lst] + cnt);
		return;
	}
	if (suan(lst, pos))
	{ // 上一行当前非零
		if (a[x][m - pos + 1])
			return;
		if (suan(lst, pos) == 2)
			dfs(x, lst, now * 3 + 1, pos - 1, cnt);
		else
			dfs(x, lst, now * 3, pos - 1, cnt);
	}
	else
	{
		dfs(x, lst, now * 3, pos - 1, cnt); // 什么都不放，跳！
		if (pos >= 2 && ifok(x, m - pos + 1, lst) && ifok(x, m - pos + 2, lst))
		{ // 尝试放 3*2 的 （竖的）
			dfs(x, lst, (now * 3 + 2) * 3 + 2, pos - 2, cnt + 1);
		}
		if (pos >= 3 && ifok(x, m - pos + 1, lst) && ifok(x, m - pos + 2, lst) && ifok(x, m - pos + 3, lst))
		{ // 尝试放 2*3 的 （横的）
			dfs(x, lst, ((now * 3 + 1) * 3 + 1) * 3 + 1, pos - 3, cnt + 1);
		}
	}
}
int main()
{
	// freopen("a.in","r",stdin);
	init();
	cin >> T;

	while (T--)
	{

		cin >> n >> m >> k;
		memset(a, 0, sizeof a);
		for (int i = 1; i <= k; i++)
		{
			int x, y;
			cin >> x >> y;
			a[x][y] = 1;
		}

		memset(f, -0x3f3f3f3f, sizeof f);
		f[0][0] = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < pow[m]; j++)
				f[(i + 1) % 2][j] = -0x3f3f3f3f;
			for (int j = 0; j < pow[m]; j++)
			{
				if (f[i % 2][j] < 0)
					continue;
				dfs(i + 1, j, 0, m, 0);
			}
		}
		cout << f[n % 2][0] << endl;
	}
	return 0;
}