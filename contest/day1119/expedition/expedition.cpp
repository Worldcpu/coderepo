#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MS=1024,MN=5e4+15,ML=10;
int n,q,ans,a[MN],b[MN];
bitset<MN> bit[MS];

void solve(int l,int r,int x){
    int now=l,res=0;
    while(now<=r&&x!=0){
        auto it=bit[x]._Find_next(now-1);
        if(it>r) break;
        now=it;
        res+=b[now];
        x-=a[now];
    }
    ans^=res;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        bit[a[i]][i]=1;
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int s=0;s<(1<<ML);s++){
        for(int i=1;i<=n;i++){
            if((s|a[i])==s){
                bit[s][i]=1;
            }
        }
    }
    cin>>q;
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        solve(l,r,x);
    }
    cout<<ans<<'\n';
    return 0;
}