#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],b[MN],cnta,cntb;

void init(){
    cnta=cntb=0;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnta+=a[i]==1;
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        cntb+=b[i]==1;
    }
    if(cnta!=cntb){
        cout<<"No\n";
        return ;
    }
    if(cnta==1&&(a[1]!=b[1]||a[n]!=b[n])){
        cout<<"No\n";
        return;
    }
    cout<<"Yes\n";
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}