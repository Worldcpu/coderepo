#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int MN=5e5+15;
constexpr ull base=13131;
int n,m,tmp[MN],ans[MN];
ull hsh[MN];
map<int,set<ull>> mp;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        mp[0].insert(i);
    }
    ull pw=1;
    for(int i=1;i<=m;i++){
        pw*=base;
        int num;
        cin>>num;
        set<int> st;
        for(int j=1;j<=num;j++){
            cin>>tmp[j];
            mp[hsh[tmp[j]]].erase(tmp[j]);
            st.insert(hsh[tmp[j]]);
            hsh[tmp[j]]+=pw;
            mp[hsh[tmp[j]]].insert(tmp[j]);
            st.insert(hsh[tmp[j]]);
        }
        for(auto p:st){
            if(mp[p].size()!=1){
                continue;
            }
            auto it=(*mp[p].begin());
            if(ans[it]==0){
                ans[it]=i;
            }
            mp[p].erase(it);
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    
    return 0;
}