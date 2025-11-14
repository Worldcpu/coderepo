#include "../../../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=200000;
int p[N+1];
rnd rd;

int main(){
    cout<<"1\n"; 
    cout<<N<<'\n';
    iota(p+1,p+1+N,1);
    rd.shuffle(p+1,p+1+N);
    for(int i=1;i<=N;i++) cout<<p[i]<<' ';
    cout<<'\n';
    rd.shuffle(p+1,p+1+N);
    for(int i=1;i<=N;i++) cout<<p[i]<<' ';
    cout<<'\n';
    return 0;
}