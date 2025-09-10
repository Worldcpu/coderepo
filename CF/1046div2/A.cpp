#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;


void solve(){
    cin>>a>>b>>c>>d;
    c-=a;
    d-=b;
    if(c>d) swap(c,d);
    if(a>b) swap(a,b);
    if(2*a+2>=b&&2*c+2>=d) cout<<"YES\n";
    else cout<<"NO\n";
}

int main(){
    int T;
    cin>>T;
    while(T--) solve();
}