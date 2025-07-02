#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int cf[MN],K;
string s;

namespace SA{
    int len,sa[MN],rk[MN],ork[MN],buc[MN],id[MN],ht[MN],st[30][MN];

    void getsa(string s){
        int m=1<<7,p=0;
        len=s.length();
        s=" "+s;
        memset(rk,0,sizeof(rk));
        memset(ht,0,sizeof(ht));
        memset(sa,0,sizeof(sa));
        memset(ork,0,sizeof(ork));
        memset(buc,0,sizeof(buc));
        for(int i=1;i<=len;i++) buc[rk[i]=s[i]]++;
        for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
        for(int i=len;i>=1;i--) sa[buc[rk[i]]--]=i;
        for(int w=1;;m=p,p=0,w<<=1){
            for(int i=len-w+1;i<=len;i++) id[++p]=i;
            for(int i=1;i<=len;i++) if(sa[i]>w) id[++p]=sa[i]-w;
            memset(buc,0,(m+1)<<2);
            memcpy(ork,rk,(len+1)<<2);
            p=0;
            for(int i=1;i<=len;i++) buc[rk[i]]++;
            for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
            for(int i=len;i>=1;i--) sa[buc[rk[id[i]]]--]=id[i];
            for(int i=1;i<=len;i++) rk[sa[i]]=ork[sa[i - 1]] == ork[sa[i]] && ork[sa[i - 1] + w] == ork[sa[i] + w] ? p : ++p; 
            if(p==len) break;
        }
        ht[len+1]=0;
        for(int i=1,k=0;i<=len;i++){
            if(k) k--;
            while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
            ht[rk[i]]=st[0][rk[i]]=k;
        }
    }

    void initst(){
        for(int i=1;i<=__lg(len);i++){
            for(int j=1;j+(1<<i)-1<=len;j++){
                st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }

    int lcp(int i,int j){
        if((i=rk[i])>(j=rk[j])) swap(i,j);
        int d=__lg(j-(i++));
        return min(st[d][i],st[d][j-(1<<d)+1]);
    }

}using namespace SA;

void solve(){
    cin>>s>>K;
    memset(cf,0,sizeof(cf));
    getsa(s);
    initst();
    for(int i=1;i<=len-K+1;i++){
        int l=i,r=i+K-1,L,R;
        if(l+1>r) R=len-sa[r]+1;
        else{
            int ld=l+1,rd=r;
            int d=__lg(rd-ld+1);
            R=min(st[d][ld],st[d][rd-(1<<d)+1]);
        }
        L=max(ht[l],ht[r+1])+1;
        if(L<=R){
            cf[L]++;
            cf[R+1]--;
        }
    }
    int ans=-1,maxx=1;
    for(int i=1;i<=len;i++){
        cf[i]+=cf[i-1];
        if(cf[i]>=maxx){
            ans=i;
            maxx=cf[i];
        }
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
