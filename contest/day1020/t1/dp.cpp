#include "../../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=4;

rnd rd;

int main(){
    cout<<N<<' '<<rd.gen(1,N-1)<<' '<<rd.gen(1,5)<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,10)<<' ';
    }

    return 0;
}