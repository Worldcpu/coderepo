#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int inf=1e9;


void cb(){
    int n,m;cin>>n>>m;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    if(m==1){
        int ans=0,mx=*max_element(a.begin()+1,a.end());
        vector<int>d(n+1);
        for(int i=1;i<=n;i++)d[i]=mx-a[i];
        for(int i=1;i<=n;i++)ans+=max(d[i]-d[i-1],0ll);
        cout<<ans<<'\n';
    }
    else{
        int ans=inf;
        for(int x=0;x<=150;x++){
            for(int y=x;y<=150;y++){
                int ok=0;
                for(int i=1;i<=n;i++)if(x<a[i]&&y<a[i]){
                    ok=1;
                    break;
                }
                if(ok)continue;
                vector<vector<int>>dp(n+1,vector<int>(2,inf));
                if(x>=a[1])dp[1][0]=x-a[1];
                if(y>=a[1])dp[1][1]=y-a[1];
                for(int i=2;i<=n;i++){
                    if(x>=a[i]){
                        if(dp[i-1][0]!=inf){
                            int pre=x-a[i-1];
                            int now=x-a[i];
                            dp[i][0]=min(dp[i][0],dp[i-1][0]+max(now-pre,0ll));
                        }
                        if(dp[i-1][1]!=inf){
                            int pre=y-a[i-1];
                            int now=x-a[i];
                            dp[i][0]=min(dp[i][0],dp[i-1][1]+max(now-pre,0ll));
                        }
                    }
                    if(y>=a[i]){
                        if(dp[i-1][0]!=inf){
                            int pre=x-a[i-1];
                            int now=y-a[i];
                            dp[i][1]=min(dp[i][1],dp[i-1][0]+max(now-pre,0ll));
                        }
                        if(dp[i-1][1]!=inf){
                            int pre=y-a[i-1];
                            int now=y-a[i];
                            dp[i][1]=min(dp[i][1],dp[i-1][1]+max(now-pre,0ll));
                        }
                    }
                }
                ans=min(ans,min(dp[n][0],dp[n][1]));
            }
        }
        cout<<ans<<'\n';
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        cb();
    }
    return 0;
}
