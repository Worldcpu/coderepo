#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=5;
mt19937_64 mt(random_device{}());

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    int m=getrd(5,50);
    cout<<N<<' '<<m<<'\n';
    for(int i=1;i<=N;i++){
        cout<<getrd(1,m)-getrd(1,m)<<' ';
    }
    
    return 0;
}