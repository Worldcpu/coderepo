#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4e5+15,MV=(1<<20),ML=(1<<10)-1,MOD=998244353;
int w[MV],n,a[MN];


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    fill(w,w+MV,1);
    for(int i=1;i<=n;i++){
        int high=a[i]>>10,low=a[i]&ML;
        for(int j=0;j<=ML;j++){
            if((low|j)==j){
                w[high<<10|j]=a[i]*w[high<<10|j]%MOD;
            }
        }
        int ret=1;
        for(int j=0;j<=ML;j++){
            if((high|j)==high){
                ret=ret*w[(j<<10)|low]%MOD;
            }
        }
        cout<<ret<<'\n';
    }
    return 0;
}