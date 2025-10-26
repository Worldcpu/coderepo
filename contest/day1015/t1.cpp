#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,t,a[MN],ans;
bool flag;
string st;
vector<int> vct;

bool cmp(int x,int y){
    return x>y;
}

void init(){
    flag=ans=0;
    vct.clear();
}

void solve(){
    cin>>n>>t>>st;
    init();
    st=" "+st;
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(st[i]=='0') cnt++;
        else{
            vct.push_back(cnt);
            cnt=0;
        }
    }
    vct[0]+=cnt;
    sort(vct.begin(),vct.end(),cmp);
    for(auto p:vct){
        if(!flag){
            ans+=max(0,p-1-t);
            flag=1;
        }else{
            ans+=max(0,p-2*t);
        }
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