#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e3+15;
int n,p[MN],w[MN],sumw;

void init(){
    for(int i=1;i<=n;i++) w[i]=0;
    sumw=0;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>p[i];
        for(int j=i-1;j>=1;j--){
            if(p[j]>p[i]) w[i]++;
        }
    }
    for(int i=1;i<=n;i++){
        int aft=p[i],cnt=0;
        for(int j=i+1;j<=n;j++){
            if(aft<p[j]) cnt++;
        }
        sumw+=min(cnt,w[i]);
    }
    cout<<sumw<<'\n';
    
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}