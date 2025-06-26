#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x,y;

void solve(){
    cin>>x>>y;
    if(x>y) swap(x,y);
    int ans=(y-x)*((1.0+sqrtl(5.0))/2.0);
    if(ans==x) cout<<"Farmer John\n";
    else cout<<"Bessie\n"; 
}

signed main(){
    cin>>n>>m;
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
