#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e6+15;
constexpr ll MOD=23333333333333333;
int n,m,sta[MN],top,a[MN],w[MN],L[MN],R[MN];

namespace SA{
    int len,sa[MN],rk[MN],ork[MN],buc[MN],id[MN],ht[MN],st[30][MN];

    void getsa(string s){
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

bool cmp(int x,int y){
    return rk[x]<rk[y];
}

int main(){
    string s;
    cin>>n>>m>>s;
    getsa(s);
    initst();
    while(m--){
        int t;
        ll ans=0;
        cin>>t;
        for(int i=1;i<=t;i++){
            cin>>a[i];
        }
        sort(a+1,a+1+t);
        t=unique(a+1,a+1+t)-a-1;
        sort(a+1,a+1+t,cmp);
        w[1]=0;
        for(int i=2;i<=t;i++){
            w[i]=lcp(a[i-1],a[i]);
        }
        sta[top=0]=0;
        for(int i=1;i<=t;i++){
            while(top&&w[sta[top]]>w[i]) top--;
            L[i]=sta[top];
            sta[++top]=i;
        }
        sta[top=0]=t+1;
        for(int i=t;i>=1;i--){
            while(top&&w[sta[top]]>=w[i]) top--;
            R[i]=sta[top];
            sta[++top]=i;
        }
        for(int i=2;i<=t;i++){
            ans=(ans+1ll*w[i]*(R[i]-i)%MOD*(i-L[i])%MOD)%MOD;
        }
        cout<<ans<<'\n';
    }

    return 0;
}
