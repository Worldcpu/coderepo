#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=5e5;
mt19937_64 mt(random_device{}());

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    ios::sync_with_stdio(0);
    cout<<N<<'\n';
    for(int i=1;i<=2*N;i++){
        cout<<getrd(1,2*N-1)<<' ';
    }

    
    return 0;
}