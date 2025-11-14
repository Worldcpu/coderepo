#include "../../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=10;

rnd rd;


int main(){
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,100)<<' ';
    }
    return 0;
}