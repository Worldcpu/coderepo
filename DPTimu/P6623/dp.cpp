#include "../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=10;
int fa[N+1];
rnd rd;
Graph qwq(rd);

int main(){
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,10)<<' ';
    }
    cout<<'\n';
    auto pwp=qwq.tree(N);
    for(auto [u,v]:pwp){
        if(fa[u]) fa[v]=u;
        else fa[u]=v;
    }   
    for(int i=2;i<=N;i++){
        cout<<fa[i]<<' ';
    }

    return 0;
}