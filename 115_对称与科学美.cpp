#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15;
int n,a[MN],ans,st;
mt19937 mt;
map<int,int> mp,cnt;

signed main(){
    mt.seed(time(0));
    cin>>n;
    st=mt();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!mp.count(a[i])) mp[a[i]]=(st+=mt());
        a[i]=mp[a[i]];
    }
    int pre=0;
    cnt[0]=1;
    for(int i=1;i<=n;i++){
        pre^=a[i];
        ans+=cnt[pre];
        cnt[pre]++;
    }
    cout<<ans;
    return 0;
}
