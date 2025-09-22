#include <cstdio>
#include <cstdlib>
#include <cassert>

int main () {
  FILE *f = fopen ("/dev/urandom", "r");
  int sr;
  assert (fread (&sr, 4, 1, f));
  srand (sr);
  int n = rand () % 16 + 1;
  printf ("%d\n", n);
  for (int i = 0; i < n; i++) {
    int l = rand () % 10 + 1;
    int p = rand () % (l + 1) - 1;
    for (int j = 0; j < l; j++)
      if (j != p) printf ("%d", rand () % 2); else printf ("?");
    puts ("");
  }
}
