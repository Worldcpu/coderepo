#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MW=64;
int n,w,x[MN],y[MN],ans;
vector<int> st[MW+1];

void init(){
    for(int i=0;i<=MW;i++) st[i].clear();
    ans=0;
}

void solve(){
    cin>>n>>w;
    init();
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        st[x].push_back(y);
    }
    for(int i=0;i<MW;i++){
        sort(st[i].begin(),st[i].end());
        if((w>>i)&1){
            if(!st[i].empty()){
                ans+=st[i][st[i].size()-1];
                st[i].pop_back();
            }
        }
        int sum=0;
        for(int j=st[i].size()-1,qwq=1;j>=0;j--,qwq^=1){
            sum+=st[i][j];
            if(qwq==0){
                st[i+1].push_back(sum);
                sum=0;
            }
        }
        if(sum) st[i+1].push_back(sum);
        st[i].clear();
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