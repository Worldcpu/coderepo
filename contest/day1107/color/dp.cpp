#include "../../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=10000;
int p1[N+1],p2[N+1];
rnd rd;

int main(){
    cout<<N<<'\n';
    iota(p1+1,p1+1+N,1);
    iota(p2+1,p2+1+N,1);
    rd.shuffle(p1+1,p1+1+N);
    rd.shuffle(p2+1,p2+1+N);
    int cnt=rd.gen(1,N);
    for(int i=1;i<=cnt;i++){
        swap(p1[rd.gen(1,N)],p2[rd.gen(1,N)]);
    }
    for(int i=1;i<=N;i++) cout<<p1[i]<<' '<<p2[i]<<'\n';
    return 0;
}