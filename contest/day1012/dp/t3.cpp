#include "../../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=5,M=10;
rnd rd;

int main(){
    cout<<3*N<<' '<<M<<'\n';
    for(int i=1;i<=3*N;i++){
        cout<<rd.gen(1,M)<<' ';
    }
    return 0;
}