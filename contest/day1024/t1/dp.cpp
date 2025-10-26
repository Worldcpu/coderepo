#include<bits/stdc++.h>
#include "../../random.h"
using namespace Rand;
using namespace std;
constexpr int N=10,M=3;
unordered_map<int,int> mp;
int T=100;
rnd rd;

void output(int x){
    if(x<10){
        cout<<"00"<<x<<' ';
    }else if(x>=10&&x<100){
        cout<<"0"<<x<<' ';
    }else if(x>=100&&x<1000){
        cout<<x<<' ';
    }
}

int main(){
    cout<<T<<'\n';
    while(T--){
        cout<<N<<' '<<M<<'\n';
        mp.clear();
        for(int i=1;i<=N;i++){
            int x=rd.gen(1,999);
            while(mp[x]){
                x=rd.gen(1,999);
            }
            output(x);
            mp[x]=1;
        }
        cout<<'\n';
    }
    return 0;
}