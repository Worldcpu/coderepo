#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int T,n,fa[MN],dg[MN];

void clear(){
    for(int i=1;i<=n;i++) dg[i]=fa[i]=0;
}

void solve(){
    cin>>n;
    clear();
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        dg[fa[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(dg[i]) continue;
        int pre=fa[i],len=0;
        while(dg[pre]==1){
            pre=fa[pre];
            len++;
        }
        len++;
        if(len&1){
            cout<<1<<'\n';
            return;
        }
    }
    cout<<"0\n";
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
