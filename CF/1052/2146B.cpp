#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,L[MN],ans;
vector<vector<int>> vct;
map<int,int> mp;
set<int> st;

void init(){
    ans=0;
    st.clear();
    mp.clear();
    vct.resize(n+1);
    for(int i=1;i<=m;i++){
        st.insert(i);
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=n;i++){
        cin>>L[i];
        vct[i].resize(L[i]+1);
        for(int j=1;j<=L[i];j++){
            cin>>vct[i][j];
            mp[vct[i][j]]++;
            if(st.count(vct[i][j])) st.erase(vct[i][j]);
        }
    }
    if(st.size()){
        cout<<"NO\n";
        return;
    }
    for(int i=1;i<=n;i++){
        bool flag=1;
        for(int j=1;j<=L[i];j++){
            if(--mp[vct[i][j]]==0){
                flag=0;
            }
        }
        if(flag){
            ans++;
        } 
        for(int j=1;j<=L[i];j++){
            mp[vct[i][j]]++;
        }
    }
    if(ans>=2){
        cout<<"YES\n";
    }else cout<<"NO\n";

}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}