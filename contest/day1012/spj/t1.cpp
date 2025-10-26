#include "testlib.h"

#include <vector>

using namespace std;

const int maxN = 100000;

int n, k, x[maxN], y[maxN], l[maxN], r[maxN], ja[maxN], jb[maxN], pa[maxN], pb[maxN];

int main( int argc, char *argv[] ) {
  registerTestlibCmd(argc, argv);
  n = inf.readInt();
  for (int i = 0; i < n; ++i) {
    x[i] = inf.readInt();
    y[i] = inf.readInt();
  }
  k = inf.readInt();
  for (int i = 0; i < k; ++i) {
    l[i] = inf.readInt(1, n) - 1;
    r[i] = inf.readInt(1, n) - 1;
  }

  for (int i = 0; i < k; ++i) {
    ja[i] = ans.readInt(0, n) - 1;
    jb[i] = ans.readInt(0, n) - 1;
  }
  for (int i = 0; i < k; ++i) {
    pa[i] = ouf.readInt(0, n) - 1;
    pb[i] = ouf.readInt(0, n) - 1;
    if (pa[i] == -1 && pb[i] == -1) {
      if (ja[i] != -1) {
        quitf(_wa, "������ %d: �������� �� ����� ����, ���� ��� ����������", i + 1);
      }
    } else {
      if (pa[i] < l[i] || pa[i] > r[i] || pb[i] < l[i] || pb[i] > r[i]) {
        quitf(_wa, "������ %d: �������� (%d %d) �� �������� � ������� [%d %d]", i + 1, pa[i] + 1, pb[i] + 1, l[i] + 1, r[i] + 1);
      }
      if (pa[i] == -1 || pb[i] == -1) {
        quitf(_wa, "������ %d: ������������ ���� �������� (%d %d)", i, pa[i] + 1, pb[i] + 1);
      } else if (x[pa[i]] == x[pb[i]] || y[pa[i]] == y[pb[i]]) {
        quitf(_wa, "������ %d: �������� %d � %d �� ��������� ��������", i, pa[i] + 1, pb[i] + 1);
      }
    }
  }
  quitf(_ok, "%d ��������", k);
  return -1;
}
