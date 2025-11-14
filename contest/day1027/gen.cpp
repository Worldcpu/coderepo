#include "../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=6;

rnd rd;

int main(){
    cout<<"1\n"<<N<<' '<<rd.gen(1,10)<<'\n'; 
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,5)<<' ';
    }

    return 0;
}