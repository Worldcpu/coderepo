#include "random.h"
#include<bits/stdc++.h>
using namespace Rand;
using namespace std;
constexpr int N=5,M=5;

rnd rd;
Graph gp(rd);

int main(){
    cout<<N<<' '<<M<<'\n';
    auto ret=gp.wtree(N,{1,10});
    for(auto [u,v,w]:ret) cout<<u<<' '<<v<<' '<<w<<'\n';
    for(int i=1;i<=M;i++){
        int op=rd.gen(1,3);
        cout<<op<<' ';
        if(op==1){
            cout<<rd.gen(1,N-1)<<' '<<rd.gen(2,6)<<'\n';
        }else if(op==2){
            int x=rd.gen(1,N),y=rd.gen(1,N);
            while(x==y) y=rd.gen(1,N);
            
            cout<<x<<' '<<y<<'\n';
        }else{
            cout<<rd.gen(1,N)<<' '<<rd.gen(1,N)<<' '<<rd.gen(1,N)<<'\n';
        }
    }

    return 0;
}