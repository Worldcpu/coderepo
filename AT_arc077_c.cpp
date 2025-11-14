#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,a[MN],b[MN],c[MN],ans=1e18;

void solve(int x,int y){
    b[1]+=y-x;
    b[x+1]+=x+1;
    b[y+1]-=x+1;
    c[y+1]++;
    c[x+1]--;
    if(y<=x){
        b[1]+=x+1;
        b[y+1]+=m;
        c[1]--;
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        solve(a[i],a[i+1]);
    }
    for(int i=1;i<=m;i++){
        c[i]+=c[i-1];
        b[i]+=b[i-1];
        ans=min(ans,c[i]*i+b[i]);
    }
    cout<<ans<<'\n';
    return 0;
}