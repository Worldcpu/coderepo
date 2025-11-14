#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,K,ans,pw2;
unordered_map<int,bool> vis;

void solve(int n,int k){
    for(int i=2;i*i*i<=n;i++){
        int t=i*i,cnt=2;
        while(t<=n/i){
            t*=i;
            cnt++;
            if(cnt<k) continue;
            if(vis[t]) continue;
            if((int)sqrtl(t)*sqrtl(t)==t){
                pw2++;
            }
            vis[t]=1;
            ans++;
        }
    }
}

signed main(){
    cin>>n>>K;
    solve(n,K);
    if(K==1){
        cout<<n<<'\n';
        return 0;
    }else if(K==2){
        cout<<(int)sqrtl(n)+ans-pw2<<'\n';
    }else cout<<ans+1<<'\n';
    
    return 0;
}