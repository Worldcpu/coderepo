#include<bits/stdc++.h>
using namespace std;
constexpr int N=10,MV=200,M=10;
mt19937 mt(time(0));

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

int main(){
    cout<<N<<' '<<M<<'\n';
    for(int i=1;i<=N;i++){
        cout<<getrd(0,MV)<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=M;i++){
        int l=getrd(1,N),r=getrd(1,N);
        if(l>r) swap(l,r);
        cout<<l<<' '<<r<<'\n';
    }

    return 0;
}