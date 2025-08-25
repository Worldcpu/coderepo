#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,n2,m,cnt1,a[MN];
string st;

void init(){
    cnt1=__lg(1245);
    cnt1=0;
}

void solve(){
    cin>>n>>m>>st;
    st=" "+st;
    init();
    for(int i=1;i<=n;i++){
        cnt1+=(st[i]=='1');
    }
    if((m*cnt1)%n){
        cout<<-1<<'\n';
        return;
    }
    for(int i=1;i<=n;i++){
        a[i]=st[i]-'0';
        a[i+n]=st[i]-'0';
    }
    n2=n<<1;
    for(int i=1;i<=n2;i++){
        if(a[i]){
            a[i]=n-cnt1;
        }else a[i]-=cnt1;
    }
    for(int i=1;i<=n2;i++) a[i]+=a[i-1];
    int l=0,r=0;
    for(int i=m;i<=n2;i++){
        if(a[i-m]==a[i]) {l=i-m+1,r=i;break;}
    }
    if(r<=n){
        cout<<1<<'\n'<<l<<' '<<r<<'\n';
    }else cout<<2<<'\n'<<1<<' '<<r-n<<'\n'<<l<<' '<<n<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}