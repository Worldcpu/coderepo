#include "../../random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=5;

rnd rd;

int main(){
    cout<<"1 1\n";
    cout<<N<<' '<<rd.gen(1,N)<<'\n';
    for(int i=1;i<=2;i++){
        for(int j=1;j<=N;j++){
            cout<<rd.gen(0,1);
        }
        cout<<'\n';
    }
    return 0;
}
