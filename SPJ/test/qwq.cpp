#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1000005;
ll n;
bool ac[N];
int main(){
  cin>>n;
  for(int i = 1; i <= n; i++) {
    ac[i]=(((n - i + 1) % 2) == 0);
  }
  cout << ac[n] << " " << (((n-n+1)%2)==0) << "\n";
  return 0;
}
