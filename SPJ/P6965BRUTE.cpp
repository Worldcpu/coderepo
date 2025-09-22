#include <cstdio>
#include <cassert>
#include <vector>

int main() {
  int n;
  assert(1 == scanf("%d", &n));
  std::vector<std::vector<int> > words(n);
  std::vector<int> id(n);
  std::vector<int> qPos(n, -1);
  int cn = 0;
  for (int i = 0; i < n; i++) {
    int c = getchar();
    while (c <= 32) c = getchar();
    int pos = -1;
    while (c > 32) {
      if (c == '?') {
        pos = (int) words[i].size();
      }
      words[i].push_back(c == '?' ? -1 : (c - '0'));
      c = getchar();
    }
    if (pos >= 0) {
      id[cn++] = i;
      qPos[i] = pos;
    }
  }
  for (int i = 0; i < 1 << cn; i++) {
    for (int j = 0; j < cn; j++) {
      words[id[j]][qPos[id[j]]] = (i >> j) & 1;
    }
    bool ok = true;
    for (int i = 0; ok && i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        int k = 0;
        while (k < (int) words[i].size() && k < (int) words[j].size() && words[i][k] == words[j][k]) ++k;
        if (k == (int) words[i].size() || k == (int) words[j].size()) {
          ok = false;
          break;
        }
      }
    }
    if (ok) {
      puts("YES");
      for (int i = 0; i < n; i++) {
        for (int j : words[i]) {
          putchar(j + '0');
        }
        puts("");
      }
      return 0;
    }
  }
  puts("NO");
}
