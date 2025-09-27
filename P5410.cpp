#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
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
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }
}bit;

namespace EXKMP{
    int nxt[MN];

    void initnxt(string s){
        int len=s.length(),p=0,k=1,l;
        nxt[0]=len;
        while(p+1<len&&s[p]==s[p+1]) p++;
        nxt[1]=p;
        for(int i=2;i<len;i++){
            p=k+nxt[k]-1;
            l=nxt[i-k];
            if(i+l<=p) nxt[i]=l;
            else{
                int j=max(0,p-i+1);
                while(i+j<len&&s[i+j]==s[j]) j++;
                nxt[i]=j;
                k=i;
            }
        }
    }
}using namespace EXKMP;

void init(){
    bit.clear();
    for(int i=0;i<=st.length();i++){
        nxt[i]=0;
    }
    for(int i=0;i<26;i++){
        cnt[i]=cntp[i]=cnts[i]=0;
    }
    pre=suf=ans=tot=0;
}

void solve(){
    cin>>st;
    init();
    n=st.length();
    initnxt(st);
    for(int i=0;i<st.length();i++){
        cnt[st[i]-'a']++;
    }
    for(int i=0;i<26;i++){
        tot+=(cnt[i]&1);
    }
    suf=tot;
    for(int i=0;i<st.length();i++){
        if((++cntp[st[i]-'a'])&1) pre++;
        else pre--;
        if((--cnts[st[i]-'a'])&1) suf++;
        else suf--;
        if(i>0){
            int x=nxt[i+1]/i;
            ans+=(x/2+(x&1))*bit.query(suf+1)+(x/2)*bit.query(tot+1);
        }
        bit.modify(pre+1,1);
    }
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}