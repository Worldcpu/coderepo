#include<bits/stdc++.h>
using namespace std;
int n, K,mx;
string st;
map<string, int> mp;

int main(){
    cin >> n >> K >> st;

    for(int i = 0; i <= n - K; i++){
        mp[st.substr(i, K)]++;
    }
    for(auto &p : mp){
        mx =max(mx, p.second);
    }
    vector<string> ans;
    for(auto &p : mp){
        if(p.second == mx){
            ans.push_back(p.first);
        }
    }
    sort(ans.begin(), ans.end());
    cout<<mx<<'\n';
    for(auto p:ans){
        cout<<p<<' ';
    }

    return 0;
}
