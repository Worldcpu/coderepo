#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,ans,a[MN];


int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]*=2;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        a[u]+=w;
        a[v]+=w;
    }
    sort(a+1,a+1+n);
    for(int i=n;i>=1;i-=2){
        ans+=a[i]-a[i-1];
    }
    cout<<ans/2;

    return 0;
}