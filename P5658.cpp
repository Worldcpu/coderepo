#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; 
    cin >> s;
    int n = s.size();
    vector<int> pref(n+1,0);
    for(int i=1;i<=n;i++)
        pref[i] = pref[i-1] + (s[i-1]=='('?1:-1);

    unordered_map<int,int> last; // 最近出现的位置
    last[0] = 0; 
    long long ans = 0;

    for(int i=1;i<=n;i++){
        if(last.count(pref[i]-1)) ans += i - last[pref[i]-1];
        last[pref[i]] = i; // 更新最近出现的位置
    }
    cout << ans << "\n";
}
