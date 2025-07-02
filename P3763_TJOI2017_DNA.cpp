#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m;
string s,t;

namespace SA{
    int len,sa[MN],rk[MN],ork[MN],buc[MN],id[MN],ht[MN],st[30][MN];

    void getsa(string s){
        memset(ork,0,sizeof(ork));
        memset(buc,0,sizeof(buc));
        int m=1<<7,p=0;
        len=s.length();
        s=" "+s;
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
        for(int i=1,k=0;i<=len;i++){
            if(k) k--;
            while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
            ht[rk[i]]=st[0][rk[i]]=k;
        }
    }

    void initst(){
        for(int i=1;i<=__lg(len);i++){
            for(int j=1;j+(1<<i)-1<=len;j++){
                st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
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
    cin>>s>>t;
    n=s.length(),m=t.length();
    s=" "+s,t=" "+t;
    string sst;
    for(int i=1;i<=n;i++){
        sst.push_back(s[i]);
    }
    sst.push_back('#');
    for(int i=1;i<=m;i++){
        sst.push_back(t[i]);
    }
    getsa(sst);
    initst();
    int ret=0;
    for(int i=1;i<=n-m+1;i++){
        int curs=i,curt=1;
        for(int j=1;j<=4;j++){
            if(curt<=m){
                int lcpl=lcp(curs,curt+n+1);
                curs+=lcpl+(j<4);
                curt+=lcpl+(j<4);
            }
        }
        ret+=curt>m;
    }
    cout<<ret<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
