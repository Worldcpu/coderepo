#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,nxt[MN];
string s;

void clear(){
    for(int i=0;i<=n;i++) nxt[i]=0;
}

void getnxt(){
    for(int i=2,j=0;i<=n;i++){
        while(j>0&&s[i]!=s[j+1]) j=nxt[j];
        if(s[i]==s[j+1]) j++;
        nxt[i]=j;
    }
}

void solve(){
    n=s.length();
    s=" "+s;
    getnxt();
    if(n%(n-nxt[n])==0) cout<<n/(n-nxt[n])<<'\n';
    else cout<<1<<'\n';
}

int main(){
    while(cin>>s){
        if(s==".") break;
        solve();
    }
    return 0;
}
