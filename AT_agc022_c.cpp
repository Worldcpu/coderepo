#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55;
int n,a[MN],b[MN],ans;
bool vis[MN];
bitset<MN> f[MN];

bool solve(){
    for(int i=1;i<=n;i++) f[i].reset();
    for(int i=1;i<=n;i++){
        f[i][a[i]]=1;
    }
    for(int i=50;i>=1;i--){
        if(vis[i]){
            for(int j=1;j<=n;j++){
                for(int k=a[j];k>=i;k--){
                    f[j][k%i]=f[j][k%i]|f[j][k];
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!f[i][b[i]]) return 0;
    }
    return 1;
}   

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    fill(vis,vis+MN,1);
    if(!solve()){
        cout<<-1<<'\n';
        return 0;
    }
    for(int i=50;i>=0;i--){
        vis[i]=0;
        if(!solve()){
            ans+=(1ll<<i);
            vis[i]=1;
        }       
    }
    cout<<ans;

    return 0;
}