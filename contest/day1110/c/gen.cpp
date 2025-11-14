#include<bits/stdc++.h>
#include "../../random.h"
using namespace Rand;
using namespace std;
constexpr int N=8;

rnd rd;

int main(){
    cout<<N<<'\n'; 
    for(int i=1;i<=N;i++){
        cout<<1<<' '<<fixed<<setprecision(2)<<rd.gen(0.5,2.0)<<' '<<rd.gen(20,50)<<'\n';
    }
    cout<<N<<'\n';
    for(int i=1;i<=N;i++){
        int op=rd.gen(1,2);
        cout<<op<<' ';
        if(op==1){
            int l=rd.gen(1,N),r=rd.gen(l,N),x=rd.gen(1,50);
            cout<<l<<' '<<r<<' '<<x<<'\n';
        }else{
            cout<<rd.gen(1,N)<<' '<<1<<' '<<fixed<<setprecision(2)<<rd.gen(0.5,2.0)<<' '<<rd.gen(20,50)<<'\n';
        }
    }
    return 0;
}