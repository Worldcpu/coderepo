#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,r,c,x[MN],y[MN],a[MN];
pir mx[MN];
int cnt[MN],ans,ret[MN],cmxid[MN],mxid[MN];
priority_queue<pir> q[MN];

signed main(){
    cin>>n>>r>>c;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i]>>a[i];
    }
    for(int i=1;i<=n;i++){
        if(mx[y[i]].second<a[i]){
            q[y[i]].push(mx[y[i]]);
            mx[y[i]]=pir(x[i],a[i]);
        }else if(mx[y[i]].second==a[i]) q[y[i]].push(pir(x[i],a[i]));
        else q[y[i]].push(pir(x[i],a[i]));
    }
    for(int i=1;i<=c;i++){
        ans+=mx[i].second;
        while(!q[i].empty()){
            auto tp=q[i].top();
            q[i].pop();
            ret[tp.first]=max(ret[tp.first],tp.second);
        }       
    }
    cerr<<ans<<'\n';
    for(int i=1;i<=r;i++){
        ans+=ret[i];
    }
    cout<<ans<<'\n';
    return 0;
}