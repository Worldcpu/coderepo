#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+51;
int top,sta[MN],L[MN],R[MN],ans;
string s;

namespace SA{
    int len,sa[MN],rk[MN],ork[MN],buc[MN],id[MN],ht[MN],st[30][MN];

    void clear(){
        memset(sa,0,sizeof(sa));
        memset(rk,0,sizeof(rk));
        memset(ork,0,sizeof(ork));
        memset(buc,0,sizeof(buc));
        memset(id,0,sizeof(id));
        memset(ht,0,sizeof(ht));
        memset(st,0,sizeof(st));
    }

    void getsa(string s){
        clear();
        len=s.length();
        s=" "+s;
        int m=1<<7;
        for(int i=1;i<=len;i++) buc[rk[i]=s[i]]++;
        for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
        for(int i=len;i>=1;i--) sa[buc[rk[i]]--]=i;
        for(int w=1,p=0;;m=p,p=0,w<<=1){
            for(int i=len-w+1;i<=len;i++) id[++p]=i;
            for(int i=1;i<=len;i++) if(sa[i]>w) id[++p]=sa[i]-w;
            memset(buc,0,sizeof(buc));
            memcpy(ork,rk,sizeof(rk));
            p=0;
            for(int i=1;i<=len;i++) buc[rk[id[i]]]++;
            for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
            for(int i=len;i>=1;i--) sa[buc[rk[id[i]]]--]=id[i];
            for(int i=1;i<=len;i++) 
                rk[sa[i]]=(ork[sa[i-1]]==ork[sa[i]]&&ork[sa[i-1]+w]==ork[sa[i]+w])?p:++p;
            if(p==len) break;
        }
        for(int i=1,k=0;i<=len;i++){
            if(k) k--;
            while(i+k<=len&&sa[rk[i]-1]+k<=len&&s[i+k]==s[sa[rk[i]-1]+k]) k++;
            ht[rk[i]]=k;
        }
    }
}using namespace SA;

signed main(){
    cin>>s;
    getsa(s);
    sta[top=1]=1;
    for(int i=2;i<=len;i++){
        while(top&&ht[sta[top]]>ht[i]) R[sta[top--]]=i;
        L[i]=sta[top];
        sta[++top]=i;
    }
    while(top) R[sta[top--]]=len+1;
    ans=len*(len-1)*(len+1)/2;
    for(int i=2;i<=len;i++){
        ans-=2*(R[i]-i)*(i-L[i])*ht[i];
    }
    cout<<ans;
    return 0;
}
