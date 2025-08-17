#include<bits/stdc++.h>
using namespace std;
int a,b;

void solve(){
    cin>>a>>b;
    int d=abs(a*a-b*b);
    cout<<((d-1)/2)+max(0,(d/4)-1)<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}