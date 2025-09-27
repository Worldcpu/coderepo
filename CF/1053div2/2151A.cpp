#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m;

void solve(){
    cin>>n>>m;
    bool flag=1;
    int lst=0;
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        if(lst==0){
            lst=x;
            continue;
        }
        if(x!=lst+1){
            flag=0;
        }
        lst=x;
    }
    if(flag){
        cout<<n-lst+1<<'\n';
    }else cout<<1<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}