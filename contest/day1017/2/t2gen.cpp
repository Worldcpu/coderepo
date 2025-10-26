#include "../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=100;

rnd rd;
Graph gp;

int main(){
    cout<<N<<'\n';
    auto ret=gp.wtree(N,{800,1000});
    for(int i=1;i<=N;i++){
        cout<<rd.gen(100,200)<<' ';
    }
    cout<<'\n';
    for(auto [u,v,w]:ret){
        cout<<u<<' '<<v<<' '<<w<<'\n';
    }


    return 0;
}
