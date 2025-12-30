#include<bits/stdc++.h>
#include "../../random.h"
using namespace std;
using namespace Rand;
constexpr int N=50,M=2,V=100;

rnd rd;

int main(){
    cout<<1<<'\n'<<N<<' '<<rd.gen(1,M)<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,V)<<' ';
    }
    
    return 0;
}