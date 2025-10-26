#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[4],p[4];

void solve(){
    cin>>a[1]>>a[2]>>a[3];
    sort(a+1,a+1+3);
    p[1]=a[1]&1,p[2]=a[2]&1,p[3]=a[3]&1;
    if((a[1]+a[2]+a[3])%3!=0||(p[1]!=p[2]||p[2]!=p[3]||p[3]!=p[1])){
        cout<<-1<<'\n';
        return;
    }
    int ans=(a[1]+a[2]+a[3])/3;
    cout<<(abs(a[1]-ans)+abs(a[2]-ans)+abs(a[3]-ans))/4<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}