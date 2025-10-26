#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,sum[MN];


signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        l--;
        for(int j=1,lst;j<=l;j=lst+1){
            lst=min(l/(l/j),r/(r/j));
            if(l/j<r/j){
                sum[j]++;
                sum[lst+1]--;
            }
        }
        sum[l+1]++;
        sum[r+1]--;
    }
    for(int i=1;i<=m;i++){
        sum[i]+=sum[i-1];
    }
    for(int i=1;i<=m;i++){
        cout<<sum[i]<<'\n';       
    }

    return 0;
}