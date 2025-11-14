#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN];
long long sum;

void init(){
    sum=0;
}

void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]); 
        sum+=a[i];
    }
    int mx=*max_element(a+1,a+1+n);
    cout<<(sum-mx>=mx-1?"Yes\n":"No\n"); 
}

signed main(){
    int T;
    scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}