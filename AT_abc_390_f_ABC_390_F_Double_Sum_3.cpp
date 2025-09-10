#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int pre[MN],n,ans,ret;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        ret+=i-pre[v]-max(pre[v-1]-pre[v],0ll)-max(pre[v+1]-pre[v],0ll);
        ans+=ret;
        pre[v]=i;
    }
    cout<<ans;
    return 0;
}