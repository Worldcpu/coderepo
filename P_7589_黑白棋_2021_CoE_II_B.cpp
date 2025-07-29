#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,K,d,ret;

void solve(){
    cin>>n>>K>>d;
    ret=0;
    for(int i=1;i<=n;i++){
        int y,b,w;
        cin>>y>>b>>w;
        ret^=(abs(b-w)-1);
    }
    cout<<(ret?"Yes":"No")<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}