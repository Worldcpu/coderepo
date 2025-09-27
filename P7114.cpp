#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15;
int n,pre,suf,tot,cnt[MN],cntp[MN],cnts[MN],ans;
string st;

struct BIT{
    int t[MN];

    void clear(){
        memset(t,0,sizeof(t));
    }

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x>0){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }
}bit;

namespace EXKMP{
    int nxt[MN];

    void initnxt(){
        int l=0,r=0;
        nxt[1]=n;
        for(int i=2;i<=n;i++){
            nxt[i]=0;
            if(i<=r) nxt[i]=min(r-i+1,nxt[i-l+1]);
            for(;i+nxt[i]<=n&&st[i+nxt[i]]==st[nxt[i]+1];++nxt[i]);
            if(i+nxt[i]-1>r) l=i,r=i+nxt[i]-1;
        }
        for(int i=1;i<=n;i++) nxt[i]=min(nxt[i],n-i);
    }
}using namespace EXKMP;

void init(){
    bit.clear();
    for(int i=1;i<=n;i++){
        nxt[i]=0;
    }
    for(int i=0;i<26;i++){
        cnt[i]=cntp[i]=cnts[i]=0;
    }
    pre=suf=ans=tot=0;
}

void solve(){
    cin>>st;
    n=st.length();
    init();
    st=" "+st;
    initnxt();
    for(int i=1;i<=n;i++){
        cnts[st[i]-'a']++;
    }
    for(int i=0;i<26;i++){
        tot+=(cnts[i]&1);
    }
    suf=tot;
    for(int i=1;i<n;i++){
        if((++cntp[st[i]-'a'])&1) pre++;
        else pre--;
        if((--cnts[st[i]-'a'])&1) suf++;
        else suf--;
        if(i>1){
            int x=nxt[i+1]/i+1;
            ans+=(x/2+(x&1))*bit.query(suf+1)+(x/2)*bit.query(tot+1);
        }
        bit.modify(pre+1,1);
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}