#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int n,a[MN],b[MN],mn,mx,res[MN];

void init(){
    for(int i=1;i<=n;i++){
        res[i]=0;
    }
    mn=mx=1;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        if(a[mn]*b[i]>a[i]*b[mn]){
            mn=i;
        }
        if(a[mx]*b[i]<a[i]*b[mx]){
            mx=i;
        }
    }
    if(mn==mx){
        cout<<"No\n";
        return;
    }
    cout<<"Yes\n";
    res[mx]=(a[mn]+b[mn]);
    res[mn]=-(a[mx]+b[mx]);
    for(int i=1;i<=n;i++){
        cout<<res[i]<<' ';
    }
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