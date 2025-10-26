#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=6,MOD=998244353;
constexpr ull base=13131;
int n;
vector<int> vct;
deque<int> p;
unordered_map<string,bool> visS;
unordered_map<int,bool> mp,visQ;

ull gethsh(const vector<int> &x){
    ull ret=0;
    for(auto p:x){
        ret=ret*base+p;
    }
    return ret;
}

void dfs(string st,deque<int> vct,vector<int> a){
    if(visS[st]) return;
    visS[st]=1;
    if(st.length()==n){
        mp[gethsh(a)]=1;
        return;
    }
    if(!vct.size()) return;

    int tmp=vct.front();
    vct.pop_front();
    dfs(st+"L",vct,a);
    vct.push_front(tmp);

    tmp=vct.back();
    vct.pop_back();
    dfs(st+"R",vct,a);
    vct.push_back(tmp);

    a.push_back(*min_element(vct.begin(),vct.end()));
    dfs(st+"Q",vct,a);
}

void init(){
    p.clear();
    visS.clear();
    mp.clear();
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        p.push_back(x);
    }
    dfs("",p,vct);
    cout<<mp.size()<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}