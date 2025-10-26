#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],cf[MN],ans;
vector<int> vct[2];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cf[i]=a[i]-a[i-1];
    }   
    for(int i=2;i<=n;i++){
        vct[i&1].push_back(cf[i]);
    }
    sort(vct[0].begin(),vct[0].end());
    sort(vct[1].begin(),vct[1].end());

    ans=a[1]*n;
    for(int i=0;i<vct[0].size();i++){
        int pos=(i+1)*2;
        ans+=vct[0][i]*(n-pos+1);
    }
    for(int i=0;i<vct[1].size();i++){
        int pos=(i+1)*2+1;
        ans+=vct[1][i]*(n-pos+1);
    }
    cout<<ans;
    return 0;
}