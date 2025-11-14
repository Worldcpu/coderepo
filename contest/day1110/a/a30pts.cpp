#include<bits/stdc++.h>
using namespace std;
int a,b,c;
vector<int> op;

void init(){
    op.clear();
}

void solve(){
    cin>>a>>b>>c;
    init();
    while(b){
        b>>=1;
        op.push_back(2);
    }
    op.push_back(4);
    cout<<op.size()<<'\n';
    for(auto p:op) cout<<p<<' ';
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}