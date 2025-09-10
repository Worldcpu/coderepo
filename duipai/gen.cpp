#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=50,M=5e4;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
string s[3]={"qwqwqwq","block","ask"};

int getrd(int l,int r){
    return rnd()%(r-l+1)+l;
}

signed main(){
    ios::sync_with_stdio(0);
    cout.tie(0);
    freopen("dp.in","w",stdout);
    cout<<N<<' '<<M<<'\n';
    for(int i=1;i<=M;i++){
        int op=getrd(1,2),l=getrd(1,(1<<N)-1),r=getrd(1,(1<<N)-1);
        if(l>r) swap(l,r);
        cout<<s[op]<<' '<<l<<' '<<r<<'\n';
    }
}
