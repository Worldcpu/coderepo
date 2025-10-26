#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b;

void solve(){
    cin>>n>>a>>b;
    if(n%(a+b)==0||n%(a+b)>a){
        cout<<0<<'\n';
        return;
    }
    if(n%(a+b)<=a){
        if(n<a+b){
            cout<<"Sayonara\n";
        }else{
            cout<<(n%(a+b))<<'\n';
        }
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}