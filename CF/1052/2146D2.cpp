#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,l,r,ans;
map<int,int> p;

int gpos(int x,int k){
    return (x>>k)&1;
}

void calc(int l,int r,int pos){
    if(l>r) return;
    if(l==r){
        p[l]=l;
        return;
    }
    int k=l;
    while(k+1<=r&&gpos(k+1,pos)==gpos(l,pos)) k++;
    if(k==r){
        calc(l,r,pos-1);
        return;
    }
    int itl=k,itr=k+1;
    while(itr-1>=l&&itl+1<=r){
        itr--,itl++;
        p[itr]=itl;
        p[itl]=itr;
    }
    calc(l,itr-1,pos-1);
    calc(itl+1,r,pos-1);
}

void init(){
    ans=0;
    p.clear();
}

void solve(){
    cin>>l>>r;
    init();
    calc(l,r,29);
    for(int i=l;i<=r;i++){
        ans=(ans+(p[i]|i));
    }
    cout<<ans<<'\n';;
    for(int i=l;i<=r;i++) cout<<p[i]<<' ';
    cout<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}