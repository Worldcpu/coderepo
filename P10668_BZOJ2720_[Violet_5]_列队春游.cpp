#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,sum,a[MN],cnt[MN];
double ans;


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnt[a[i]]++;
    }
    for(int i=1;i<=1e3;i++){
        ans+=1.0*cnt[i]*(n+1)/(n-sum+1);
        sum+=cnt[i];
    }
    cout<<fixed<<setprecision(2)<<ans;
    return 0;
}
