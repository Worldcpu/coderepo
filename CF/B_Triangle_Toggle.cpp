#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,dg[MN];


signed main(){
    cin>>n>>m;
    if(m==0){
        cout<<n*(n-1)/2<<'\n';
        return 0;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        dg[u]++;
        dg[v]++;
    }
    int sum=0;
    for(int i=1;i<=n;i++){
        if((dg[i]&1)!=((n-1)&1)) sum++;
    }
    cout<<n*(n-1)/2-sum/2;

    return 0;
}