
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int MN=8e5+15;
constexpr ull base=13131;
int n;
string s;
ull hsh1[MN],hsh2[MN],pw[MN];

ull gethsh1(int l,int r){
    return hsh1[r]-hsh1[l-1]*pw[r-l+1];
}

ull gethsh2(int l,int r){
    return hsh2[l]-hsh2[r+1]*pw[r-l+1];
}

void solve(){
    n=s.length();
    s=" "+s;
    pw[0]=1;
    hsh1[0]=hsh2[n+1]=0;
    for(int i=1;i<=n;i++){
        hsh1[i]=hsh1[i-1]*base+s[i];
        pw[i]=pw[i-1]*base;
    }
    for(int i=n;i>=1;i--){
        hsh2[i]=hsh2[i+1]*base+s[i];
    }
    for(int i=1;i<=n;i++){
        int mid1=(i+n)>>1,mid2=((i+n)&1?mid1+1:mid1);
        if(gethsh1(i,mid1)==gethsh2(mid2,n)){
            cout<<s;
            for(int j=i-1;j>=1;j--) cout<<s[j];
            break;
        }
    }
    cout<<'\n';
}

int main(){
    while(cin>>s){
        solve();
    }
}

