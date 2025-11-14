#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN];
map<int,int> mp;

void init(){
    mp.clear();
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    if(n&1){
        cout<<"Second\n";
        return;
    }else{
        for(int i=1;i<=n;i++){
            if(mp[a[i]]&1){
                cout<<"First\n";
                return;
            }
        }
        cout<<"Second\n";
        return;
    }
    
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}