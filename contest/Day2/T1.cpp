#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,K;
string s,t;

void solve(){
    cin>>n>>K>>s>>t;
    string cs=s.substr(max(n-K,0),max(K*2-n,0));
    string ct=t.substr(max(n-K,0),max(K*2-n,0));
    if(cs!=ct){
        cout<<"NO\n";
        return;
    }
    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    if(s!=t) cout<<"NO\n";
    else cout<<"YES\n";
}

int main(){
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
