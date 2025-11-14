#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=998244353;
int pw[MN],n,ans;
bool vis[MN];
bitset<MN> a[MN];

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
}

void init(){
    for(int i=1;i<=n;i++){
        vis[i]=0;
        a[i].reset();
    }
    ans=1;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            a[i][j]=x;
        }
    }   

    for(int i=1;i<=n;i++){
        if(!a[1][i]||!a[i][1]){
            cout<<0<<'\n';
            return;
        }
    }
    for(int i=2;i<=n;i++){
        for(int j=2;j<=n;j++){
            if(((a[i]|a[j])==a[i])||(a[i]|a[j])==a[j]){
                if(!a[i][j]){
                    cout<<0<<'\n';
                    return;
                }
            }else if(a[i][j]){
                cout<<0<<'\n';
                return;
            }
        }
    }   
    for(int i=2;i<=n;i++){
        if(vis[i]) continue;
        int cnt=1;
        vis[i]=1;
        for(int j=i+1;j<=n;j++){
            if(a[i]==a[j]){
                cnt++;
                vis[j]=1;
            }
        }
        ans=ans*pw[cnt]%MOD;
    }
    cout<<ans<<'\n';
}

signed main(){
    initpw();
    int T;
    cin>>T;
    while(T--){
        solve();
    }   
    return 0;
}