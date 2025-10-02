#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,p[MN];
string st;

void init(){
    for(int i=1;i<=n;i++){
        p[i]=i;
    }
}

void solve(){
    cin>>n>>st;
    init();
    st=" "+st;
    int l=1;
    while(l<=n){
        if(st[l]=='1'){
            l++;
            continue;
        }
        int r=l;
        while(r<n&&st[r+1]=='0') r++;
        if(r-l+1==1){
            cout<<"NO\n";
            return;
        }
        for(int k=l;k<=r;k++){
            p[k]=k+1;
        }
        p[r]=l;
        l=r+1;
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        cout<<p[i]<<' ';
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