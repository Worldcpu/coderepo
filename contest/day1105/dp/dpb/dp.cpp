#include "../../../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=10;

rnd rd;

int main(){
    cout<<"2\n"; 
    cout<<N<<' '<<rd.gen(0,10)<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(0,10)<<' ';
    }
    cout<<'\n';
    cout<<N<<' '<<rd.gen(0,10)<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(0,10)<<' ';
    }
    return 0;
}