#include <bits/stdc++.h>
using namespace std;

void solve() {	
	int n;
	cin >> n;
	
	string a, b, c;
	cin >> a >> b >> c;
	
	int ans = (a[0] == b[n - 2]) + (a[0] == c[n - 1]) + (b[n - 2] == c[n - 1]);
	
	map<char, int> cnt;
	set<char> tot;
	
	auto ins = [&](char ch) -> void {
		if (++cnt[ch] == 1) tot.emplace(ch);
	};
	auto del = [&](char ch) -> void {
		if (--cnt[ch] == 0) tot.erase(ch);
	};
	
	auto chk = [&](char c1, char c2) -> bool {
		for (char c : tot)
			if (c != c1 && c != c2) return true;
		return false;
	};
	
	auto mat = [&](const string &s1, const string &s2, int i, int j, int k) -> int {
		int d = 0;
		for (; i + d < j && j + d < k && d < 3; ++d)
			if (s1[i + d] != s2[j + d]) break;
		return d;
	};
	
	auto calc = [&](int i, int j) -> int {
		int res = mat(a, b, 0, i, j) + mat(b, c, i, j, n) + mat(a, c, 0, j, n);
		return res;
	};
	
	for (int i = 5; i < n; ++i) ins(c[i]);
	
	for (int i = 1; i + 1 < n; ++i) {
		
		for (int c = 1; i + c < n && c <= 3; ++c)
			ans = min(ans, calc(i, i + c));
		
		int mat1 = mat(a, b, 0, i, n);
		
		if (chk(b[i], a[0])) ans = min(ans, mat1);
		else ans = min(ans, mat1 + (c.back() == b[i]) + (c.back() == a[0]));
		
		del(c[i + 4]);
	}
	
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}
