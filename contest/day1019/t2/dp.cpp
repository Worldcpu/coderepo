#include "../../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=5,K=5,EK=3,S=3;
int a[N];
rnd rd;
Graph gp(rd);

int main(){
    cout<<1<<'\n';
    cout<<N<<' '<<K+EK<<'\n';
    for(int i=0;i<N;i++) a[i]=i;
    auto ret=gp.dag(N,K,0);
    for(auto [u,v,w]:ret){
        cout<<u<<' '<<v<<'\n';
    }
    for(int i=1;i<=EK;i++){
        int u,v;
        u=rd.gen(1,N),v=rd.gen(1,N);
        while(v==u) v=rd.gen(1,N);
        cout<<u<<' '<<v<<'\n';
    }
    cout<<S<<'\n';
    rd.shuffle(a,a+N);
    for(int i=0;i<S;i++){
        cout<<a[i]+1<<' ';;
    }
    return 0;
}