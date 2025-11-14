#include "../../../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=1e5;

rnd rd;

int main(){
    cout<<"2\n"; 
    cout<<N<<' '<<rd.gen(1,N-1)<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,1000000000)<<' ';
    }
    cout<<'\n';
    cout<<N<<' '<<rd.gen(1,N-1)<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,1000000000)<<' ';
    }
    return 0;
}