#include<bits/stdc++.h>
#define int long long
#define pir pair<char,char>
using namespace std;
constexpr int MN=5e5+15;
constexpr char ch[]={'A','C','G','T'};
int n,ans;
char a[MN],b[MN];
map<pir,int> cnt;

void init(){
    cnt.clear();
    ans=0;
}

void solve(){
    cin>>n;
    init();
    n=4*n;
    for(int i=1,r=0;i<=n;i++,r=(r+1)%4){
        cin>>a[i];
        b[i]=ch[r];
        if(a[i]==b[i]) continue;
        cnt[pir(a[i],b[i])]++;
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==j) continue;
            int qwq=min(cnt[pir(ch[i],ch[j])],cnt[pir(ch[j],ch[i])]);
            ans+=qwq;
            cnt[pir(ch[i],ch[j])]-=qwq;
            cnt[pir(ch[j],ch[i])]-=qwq;
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                int qwq=min({cnt[pir(ch[i],ch[j])],cnt[pir(ch[j],ch[k])],cnt[pir(ch[k],ch[i])]});
                cnt[pir(ch[i],ch[j])]-=qwq;
                cnt[pir(ch[j],ch[k])]-=qwq;
                cnt[pir(ch[k],ch[i])]-=qwq;
                ans+=qwq*2;
            }
        }
    }
    int lst=0;
    for(auto p:cnt) lst+=p.second;
    cout<<ans+(lst/4)*3<<'\n';
}


signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
