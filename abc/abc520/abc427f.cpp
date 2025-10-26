#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN = 66;
int n,m,ans;
int a[MN];
int mid;
unordered_map<int,int> R0, R1;

void dfsr(int idx, int end, int prev, int sum, bool sel) {
    if(idx > end) {
        if(sel) R1[sum%m]++;
        else R0[sum%m]++;
        return;
    }
    dfsr(idx+1,end,0,sum,sel);
    if(!prev){
        bool nfir=(sel || (idx == mid+1)); 
        dfsr(idx+1, end, 1, (sum+a[idx])%m, nfir);
    }
}

void dfsl(int idx, int end, int prev, int sum, bool sel) {
    if(idx > end) {
        int need = (m-(sum%m))%m;
        ans += R0[need];               
        if(!sel) ans += R1[need];
        return;
    }
    dfsl(idx+1,end,0,sum,0);
    if(!prev) {
        dfsl(idx+1,end,1,(sum+a[idx])%m, idx==end);
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    mid=n/2;
    dfsr(mid+1,n,0,0,0);
    dfsl(1,mid,0,0,0);
    cout<<ans;
    return 0;
}
