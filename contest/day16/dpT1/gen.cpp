#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("dp.in","w",stdout);
    int n = 10; // 可以调整
    int q = 10 ;// 可以调整
    cout << n << " " << q << "\n";

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), mt19937(chrono::steady_clock::now().time_since_epoch().count()));

    for(int i=0;i<n;i++) cout<<p[i]<<" \n"[i==n-1];

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> opdist(1,2);
    uniform_int_distribution<int> xdist(1,1e2);

    for(int i=0;i<q;i++){
        int op = opdist(rng);
        int l = uniform_int_distribution<int>(1,n)(rng);
        int r = uniform_int_distribution<int>(l,n)(rng);
        cout << op << " " << l << " " << r;
        if(op==1){
            int x = xdist(rng);
            cout << " " << x;
        }
        cout << "\n";
    }
}
