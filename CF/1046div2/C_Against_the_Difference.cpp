#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int f[MN],n,a[MN];
vector<int> pos[MN];
map<int,int> mpcnt;

void init(){
    mpcnt.clear();
    for(int i=1;i<=n;i++){
        pos[i].clear();
        f[i]=a[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]].push_back(i);
        mpcnt[i]=pos[a[i]].size();
    }
    for(int i=1;i<=n;i++){
        if(mpcnt[i]<a[i]){
            f[i]=f[i-1];
        }
        else f[i]=max(f[i-1],f[pos[a[i]][mpcnt[i]-a[i]]-1]+a[i]);
    }
    cout<<f[n]<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}