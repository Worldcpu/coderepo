#include<bits/stdc++.h>
using namespace std;
constexpr int n=500,T=1000;
int a[n+5];
map<int,bool> mp;

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

void solve(){
    mp.clear();
    cout<<n<<'\n';
    for(int i=1;i<=n;i++){
        a[i]=getrd(1,1050);
        while(mp[a[i]]) a[i]=getrd(1,n);
        mp[a[i]]=1;
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    cout<<'\n';
}

int main(){
    srand(time(0));
    ios::sync_with_stdio(0);
    freopen("dp.in","w",stdout);
    cout<<T<<'\n';
    for(int i=1;i<=T;i++) solve();

    return 0;
}