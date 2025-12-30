#include "../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=1e5;

rnd rd(std::chrono::steady_clock::now().time_since_epoch().count());
Graph gp(rd);

int main(){
    cout<<1<<'\n';
    cout<<N<<' '<<rd.gen(1,N-1)<<'\n';
    auto qwq=gp.tree(N,0.0,1.0);
    for(auto [u,v]:qwq){
        cout<<u<<' '<<v<<'\n';
    }
    return 0;
}