#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MN=2000005;

unordered_map<int,int> fa;
int n,m;
string s;
set<int> ans;
vector<int> init;

int fnd(int x){
    if(!fa.count(x)) return x;
    return fa[x]=fnd(fa[x]);
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>s;
    init.resize(m);
    for(int i=0;i<m;i++){
        cin>>init[i];
        fa[init[i]]=init[i]+1;
    }
    ans.insert(init.begin(),init.end());
    int pos=1;
    for(int i=0,bcnt=0;i<n;i++){
        if(s[i]=='A') pos++;
        else pos=fnd(pos+1),bcnt++;;
        ans.insert(pos);
        fa[pos]=fnd(pos+1);
        cerr<<pos<<' ';
        pos+=bcnt;
        cerr<<pos<<'\n';
    }
    for(int x:ans) cout<<x<<" ";
}
