#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15;
int n,ans,phi[MN],p[MN],cnt,MOD;
bool vis[MN];

void getphi(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            p[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*p[j]<=n;j++){
            vis[i*p[j]]=1;
            if(!(i%p[j])){
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }else phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
    for(int i=1;i<=n;i++){
        phi[i]+=phi[i-1];
    }
}

signed main(){
    cin>>n;
    getphi(n);
    for(int i=1;i<=cnt;i++){
        ans+=2*phi[n/p[i]]-1;
    }
    cout<<ans;
}
