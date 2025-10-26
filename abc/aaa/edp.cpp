#include "random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=200000,M=200000;
Graph gp;

int main(){
    auto ret=gp.udag(N,M,0,1,{5,100});
    cout<<N<<' '<<M<<'\n';
    for(auto [u,v,w]:ret) cout<<u<<' '<<v<<' '<<w<<'\n'; 

    return 0;
}