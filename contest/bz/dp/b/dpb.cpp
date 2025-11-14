#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e3,Q=1e4,M=571373;
mt19937 mt(random_device{}());

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

int main(){
    cout<<N<<' '<<Q<<' '<<M<<'\n';   
    for(int i=1;i<=N;i++){
        cout<<getrd(1,1e4)<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=Q;i++){
        int op=getrd(1,3),l=getrd(1,N),r=getrd(1,N);
        if(l>r) swap(l,r);
        if(op==1||op==2){
            cout<<op<<' '<<l<<' '<<r<<' '<<getrd(1,1e4)<<'\n';
        }else cout<<op<<' '<<l<<' '<<r<<'\n';
    }

    return 0;
}