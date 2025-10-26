#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,cf[MN],ans=1e9;

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        cf[l]++;
        cf[r+1]--;
    }
    for(int i=1;i<=n;i++){
        cf[i]+=cf[i-1];
        ans=min(ans,cf[i]);
    }
    cout<<ans;
    return 0;
}