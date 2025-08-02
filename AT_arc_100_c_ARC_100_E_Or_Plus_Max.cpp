#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=20,INF=1e9;
int n,ans;
pir a[1<<MN];

pir mergep(pir x,pir y){
    pir ret;
    if(x.first<y.first) swap(x,y);
    ret=x;
    if(y.first>ret.second) ret.second=y.first;
    return ret;
}


signed main(){
    cin>>n;
    for(int i=0;i<(1<<n);i++){
        int x;
        cin>>x;
        a[i]=pir(x,-INF);
    }
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++){
            if((s>>i)&1){
                a[s]=mergep(a[s],a[s^(1<<i)]);
            }
        }
    }
    for(int i=1;i<(1<<n);i++){
        ans=max(ans,a[i].first+a[i].second);
        cout<<ans<<'\n';
    }
    

    return 0;
}