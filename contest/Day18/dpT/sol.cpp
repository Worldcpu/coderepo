#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1520;
int n,ans;
map<pir,bool> vis;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(vis[pir(min(i,j),max(i,j))]) continue;
            ans+=(__gcd(i,j)==(i^j));
            vis[pir(min(i,j),max(i,j))]=1;
        }
    }
    cout<<ans;
    return 0;
}