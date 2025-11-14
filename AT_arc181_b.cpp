#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,lent,cnt[2];
string s,x,y;

namespace KMP{
    int nxt[MN];

    void initnxt(){
        nxt[1]=0;
        for(int i=2,j=0;i<=n;i++){
            while(j&&s[i]!=s[j+1]) j=nxt[j];
            if(s[i]==s[j+1]) j++;
            nxt[i]=j;
        }
    }

}using namespace KMP;

void init(){
    for(int i=1;i<=n;i++){
        nxt[i]=0;
    }
    cnt[0]=cnt[1]=0;
}

void solve(){
    cin>>s>>x>>y;
    init();

    n=s.length();
    s=" "+s;
    initnxt();
    for(auto p:x){
        cnt[p-'0']++;
    }
    for(auto p:y){
        cnt[p-'0']--;
    }
    if(!cnt[0]){
        cout<<"Yes\n";
        return;
    }
    if(!cnt[1]||n*cnt[0]%cnt[1]!=0||-n*cnt[0]/cnt[1]<0){
        cout<<"No\n";
        return;
    }
    lent=-n*cnt[0]/cnt[1];
    int gcdd=gcd(n,lent),len=n-nxt[n];
    if(n%len!=0) len=n;
    if(lent%len!=0){
        cout<<"No\n";
    }else cout<<"Yes\n";
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}