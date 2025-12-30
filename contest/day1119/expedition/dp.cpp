#include<bits/stdc++.h>
#include "../../random.h"
using namespace Rand;
using namespace std;
constexpr int N=1520,Q=1520,VA=1023,VB=1e9-7;

rnd rd;

int main(){
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,VA)<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=N;i++){
        cout<<rd.gen(1,VB)<<' ';
    }
    cout<<'\n';
    cout<<Q<<'\n';
    for(int i=1;i<=Q;i++){
        int l=rd.gen(1,N),r=rd.gen(1,N);
        while(l>r) l=rd.gen(1,N);
        cout<<l<<' '<<r<<' '<<rd.gen(1,VA)<<'\n';
    }
    return 0;
}