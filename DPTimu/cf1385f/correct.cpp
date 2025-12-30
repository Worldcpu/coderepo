#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200020;
vector<set<int> > g;
int n, k;
vector<set<int> > leaf;
queue<int> q;
struct cmp {
  bool operator()(const int x, const int y) const {
    return (leaf[x].size() == leaf[y].size()) ? x < y
                                              : leaf[x].size() > leaf[y].size();
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int tc;
  cin >> tc;
  while (tc--) {
    cin >> n >> k;
    g = leaf = vector<set<int> >(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      g[u].insert(v);
      g[v].insert(u);
    }
    for (int u = 0; u < n; u++)
      if (g[u].size() == 1) leaf[*g[u].begin()].insert(u);
    set<int, cmp> s;
    int ans = 0;
    for (int u = 0; u < n; u++) s.insert(u);
    while (true) {
      int u = *s.begin();
      if (leaf[u].size() < k) break;
      for (int i = 0; i < k; i++) {
        int v = *leaf[u].begin();
        g[v].erase(u);
        g[u].erase(v);
        s.erase(u);
        s.erase(v);
        leaf[u].erase(v);
        if (leaf[v].count(u)) leaf[v].erase(u);
        if (g[u].size() == 1) {
          int w = *g[u].begin();
          s.erase(w);
          leaf[w].insert(u);
          s.insert(w);
        }
        s.insert(v);
        s.insert(u);
      }
      ans++;
    }
    cout << ans << endl;
  }
  return 0;
}
