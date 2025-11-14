#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;

int n, d[maxn], vis[maxn];
vector<int> G[maxn];

int cnt1, cnt2; // 统计点数、入度为0的点个数
void dfs(int u){
	if(vis[u]) return ;
	vis[u] = 1;
	cnt1 ++;
	cnt2 += (d[u] == 0);
	for(int v : G[u]) dfs(v);
}

void solve()
{
	cin >> n;
	for(int i = 1; i <= n; i ++){
		int a, b; cin >> a >> b;
		G[a].push_back(b); G[b].push_back(a);
		d[b] ++; // 注意统计的还是有向图的入度
	}
	int ans = 0;
	for(int i = 1; i <= n; i ++){
		if(!vis[i]){
			cnt1 = 0, cnt2 = 0;
			dfs(i);
			if(cnt2 > 1){ cout << "-1\n"; return ; } // 无解
			if(cnt1 != 1) ans += cnt1 + 1; // 判不是自环
		}
	}
	cout << ans << '\n';
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
