#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=40,MS=(1<<21);
int f[MS],n,a[MN],m,tmp[MN],ans;
set<int> s1;

void dfs1(int pos,int sum){
    if(pos==n/2+1){
        s1.insert(sum);
        return;
    }
    dfs1(pos+1,(sum+a[pos])%m);
    dfs1(pos+1,(sum)%m);
}

void dfs2(int pos,int sum){
    if(pos==n+1){
        auto pos=s1.lower_bound(m-sum);
        pos=prev(pos);
        ans=max(ans,(sum+(*pos))%m);
        return;
    }
    dfs2(pos+1,(sum+a[pos])%m);
    dfs2(pos+1,(sum)%m);
}

signed main(){
    // freopen("s.in","r",stdin);
    // freopen("s.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]%=m;
    }
    dfs1(1,0);
    for(auto p:s1) cerr<<p<<' ';
    cerr<<'\n';
    dfs2(n/2+1,0);
    cout<<ans;


    return 0;
}