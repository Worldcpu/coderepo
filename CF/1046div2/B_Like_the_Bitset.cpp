#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int a[MN],n,K,cnt1;

void solve(){
    cnt1=0;
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        char ch;
        cin>>ch;
        a[i]=(ch=='1');
        cnt1+=a[i];
    }
    for(int i=1,j=1;i<=n;i++){
        if(j<i) j=i;
        while(j<=n&&j-i+1<=K&&a[j]==1){
            j++;
        }
        if(j-i+1>K){
            cout<<"NO\n";
            return;
        }
    }
    int cnt=0;
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        if(a[i]==0){
            cout<<(++cnt1)<<' ';
        }else cout<<(++cnt)<<' ';
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}