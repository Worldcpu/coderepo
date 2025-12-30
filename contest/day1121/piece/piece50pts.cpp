#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,B,a[MN],b[MN],lsta,res,ans;

void init(){
    lsta=res=ans=0;
}

void solve(){
    cin>>n>>B;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    priority_queue<int> q;   
    for(int i=1;i<=n;i++){
        lsta+=a[i];
        ans=max(ans,res+lsta);
        lsta-=b[i];
        res+=b[i];
        q.push(b[i]);
        while(!q.empty()&&lsta<0){
            int tp=q.top();
            q.pop();
            lsta+=tp-B;
            res-=tp;
        }
        if(lsta<0) break;
        ans=max(ans,res+lsta);
    }
    if(lsta>=0){
        ans=max(ans,res+lsta);
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