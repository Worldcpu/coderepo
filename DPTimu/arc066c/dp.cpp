#include "../random.h"
#include<bits/stdc++.h>
using namespace std;
using namespace Rand;
constexpr int N=1000;

rnd rd;
String str(rd);

int main(){
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,1000000000)<<' ';
        if(i!=N){
            cout<<str.strselect("+","-")<<' ';
        }
    }
    
    return 0;
}