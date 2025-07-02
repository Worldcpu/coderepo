#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=1e6+15;
int k1,k2,n,st[MN],top,w[MN];
ull ans,f[MN];
string s;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN];

    template<typename vct>
    void getsa(vct &s){
        int m=40000;
        len=s.size();
        s.insert(s.begin(),0);
        for(int i=1;i<=len;i++){
            x[i]=s[i];
            ++c[x[i]];
        }
        for(int i=1;i<=m;i++) c[i]+=c[i-1];
        for(int i=len;i>=1;i--) sa[c[x[i]]--]=i;
        for(int k=1;k<=len;k<<=1){
            int num=0;
            for(int i=len-k+1;i<=len;i++) y[++num]=i;
            for(int i=1;i<=len;i++){
                if(sa[i]>k) y[++num]=sa[i]-k;
            }
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=len;i++) c[x[i]]++;
            for(int i=1;i<=m;i++) c[i]+=c[i-1];
            for(int i=len;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
            swap(x,y);
            num=1,x[sa[1]]=1;
            for(int i=2;i<=len;i++){
                if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
                else x[sa[i]]=++num;
            }
            if(num==len) break;
            m=num;
        }
        for(int i=1;i<=len;i++) rk[sa[i]]=i;
        for(int i=1,k=0;i<=len;i++){
            if(k) k--;
            int j=sa[rk[i]-1];
            while(i+k<=len&&j+k<=len&&s[i+k]==s[j+k]) k++;
            ht[rk[i]]=k;
        }
    }

} using namespace SA;

ull calc1(int x){
    return x*(x+1)/2;
}

ull calc2(int x){
    return x*(x+1)*(x+x+1)/6;
}


ull solve(char lim) {
    ull cur = 0, ans = 0;
    top=0;
    memset(w,0,sizeof(w));
    for(int i = 2; i <= n; i++) {
        int wid = lim ? s[sa[i - 1] - 1] == lim : 1;
        while(top && st[top] >= ht[i]) {
            cur -= 1ull * w[top] * f[st[top]];
            wid += w[top--];
        }
        st[++top] = ht[i];
        w[top] = wid;
        cur += 1ull * wid * f[ht[i]];
        if(lim ? s[sa[i] - 1] == lim : 1) {
            ans += cur;
        }
    }
    return ans;
}

signed main(){
    cin>>s>>k1>>k2;
    n=s.length();
    for(int i=1;i<=n;i++){
        int l=max(1ll,i-k2+1),r=min(i,k1);
        if(l>r) break;
        f[i]=(calc1(r)-calc1(l-1))*(i+1)-(calc2(r)-calc2(l-1));
    }
    getsa(s);
    ans+=solve(0);
    for(int i=0;i<26;i++) ans-=solve('a'+i);
    cout<<ans;
    return 0;
}
