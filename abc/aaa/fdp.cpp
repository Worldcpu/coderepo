#include "random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=5e5,M=200;
rnd qwq;

int main(){
    cout<<N<<' '<<qwq.gen(1,10)<<' '<<qwq.gen(1,10)<<'\n';
    for(int i=1;i<=N;i++){
        cout<<qwq.gen(15,150)<<' ';
    }
    

    return 0;
}