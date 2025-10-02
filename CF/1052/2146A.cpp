#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int a[MN],n,ans;
map<int,int> cnt;

void clear(){
    cnt.clear();
    ans=0;
}

void solve(){
    cin>>n;
    clear();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnt[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        int tot=0;
        for(auto p:cnt){
            if(p.second>=i){
                tot++;
            }
        }
        tot*=i;
        ans=max(ans,tot);
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}