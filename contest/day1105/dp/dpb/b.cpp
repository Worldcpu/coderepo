#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,K,a[MN],ans;

void init(){
    ans=1e9;
}

void solve(){
    cin>>n>>K;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int l=1;l<=n;l++){
        for(int r=l;r<=n;r++){
            int mx=0;
            for(int i=l;i<=r;i++){
                for(int j=l;j<=r;j++){
                    mx=max(mx,a[i]^a[j]);
                }
            }
            if(mx>=K){
                ans=min(ans,r-l+1);
            }
        }
    }
    cout<<(ans==1e9?-1:ans)<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}