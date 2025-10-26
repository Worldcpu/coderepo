#include "../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=10000,M=1000,Z=1;
rnd rd(time(0));


int main(){
    cout<<N<<' '<<M<<' '<<Z<<'\n';
    for(int i=1;i<=M;i++){
        cout<<rd.gen(1,N)<<' '<<rd.gen(1,N)<<' '<<rd.gen(1,100)<<'\n';
    }

    return 0;
}