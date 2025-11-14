#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,K,d[MN],ans;

void work(int st){
    int res=0;
    for(int i=n,cnt=0;i>=1;i--){
        if(!((st>>(i-1))&1)){
            cnt++;
            continue;
        }
        if(cnt>=K){
            cnt-=K;
            res+=d[i];
        }else return;
    }
    ans=max(ans,res);
}

void init(){
    ans=0;
}

void solve(){
    cin>>n>>K;
    init();
    for(int i=1;i<=n;i++){
        cin>>d[i];
    }
    for(int st=0;st<(1<<n);st++){
        work(st);
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