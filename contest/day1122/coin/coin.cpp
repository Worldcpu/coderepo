#include<bits/stdc++.h>
#define int long long
#define lint __int128
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],num[MN],ans;
map<int,int> mp;

lint ksm(lint a,int b){
    lint ret=1;
    while(b){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

bool check(int x){
    for(int i=1;i<n;i++){
        if(ksm(num[i]+1,x)-1<i) return 0;
    }
    return 1;
}

signed main(){
    // freopen("coin.in","r",stdin);
    // freopen("coin.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        num[i]=a[i+1]/a[i]-1;
    }
    sort(num+1,num+n);
    ans=1;
    while(!check(ans)) ans++;
    cout<<ans;
    return 0;
}