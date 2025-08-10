#include<bits/stdc++.h>
using namespace std;
constexpr int dw=1000,up=2000;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int getrd(int l,int r){
    return rnd()%(r-l+1)+l;
}

signed main(){
    ios::sync_with_stdio(0);
    cout.tie(0);
    freopen("dp.in","w",stdout);
    int T=getrd(dw,up);
    cout<<T<<'\n';
    for(int i=1;i<=T;i++){
        int n=getrd(dw,up),m=getrd(dw,up);
        if(n>m) swap(n,m);
        cout<<n<<' '<<m<<' '<<min(n,m)-getrd(1,min(n,m)-2)<<'\n';
    }
}
