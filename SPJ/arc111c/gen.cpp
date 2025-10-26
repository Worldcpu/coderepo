#include<bits/stdc++.h>
#include "../../contest/random.h"
using namespace Rand;
using namespace std;
constexpr int N=20;
int a[N+1];
rnd rd;

int main(){
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,100)<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,100)<<' ';
    }
    cout<<'\n';
    iota(a+1,a+1+N,1);
    rd.shuffle(a+1,a+1+N);
    for(int i=1;i<=N;i++) cout<<a[i]<<' ';
    return 0;
}
