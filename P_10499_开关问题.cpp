#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int a[MN],n,K,ans;

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[i]^=x;
        a[i]|=1<<i;
    }
    int x,y;
    while(1){
        cin>>x>>y;
        if(!x&&!y) break;
        a[y]|=1<<x;
    }
    ans=1;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(a[j]>a[i]) swap(a[i],a[j]);

        }
                    if(a[i]==0){
                ans=(1<<(n-i+1));
                break;
            }
            if(a[i]==1){
                ans=0;
                break;
            }
            for(int k=n;k>=1;k--){
                if(a[i]>>k&1){
                    for(int p=1;p<=n;p++){
                        if(i!=p&&(a[p]>>k&1)) a[p]^=a[i];
                    }
                    break;
                }
            }
    }
    if(ans==0) cout<<"Oh,it's impossible~!!\n";
    else cout<<ans<<'\n';
}

int main(){
    cin>>K;
    while(K--){
        solve();
    }
    return 0;
}
