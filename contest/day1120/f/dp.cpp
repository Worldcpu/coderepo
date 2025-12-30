#include<bits/stdc++.h>
#include "../../random.h"
using namespace std;
using namespace Rand;
constexpr int N=5,V=11;

rnd rd;

int main(){
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,V)<<' ';
    }

    return 0;
}