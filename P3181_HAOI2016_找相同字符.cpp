#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int L[MN],R[MN],top,sta[MN];
string s1,s2,s3;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],st[30][MN];


    void clear(){
        memset(sa,0,sizeof(sa));
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
        memset(c,0,sizeof(c));
        memset(ht,0,sizeof(ht));
    }

    void getsa(string s){
        int m=1<<7,p=0;
        len=s.length();
        s=" "+s;
        clear();
        for(int i=1;i<=len;i++){
            x[i]=s[i];
            ++c[x[i]];
        }
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=len;i>=1;i--) sa[c[x[i]]--]=i;
        for(int k=1;k<=len;k<<=1){
            int num=0;
            for(int i=len-k+1;i<=len;i++) y[++num]=i;
            for(int i=1;i<=len;i++){
                if(sa[i]>k) y[++num]=sa[i]-k;
            }
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=len;i++) c[x[i]]++;
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
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
            if(rk[i]==1) continue;
            if(k) k--;
            int j=sa[rk[i]-1];
            while(i+k<=len&&j+k<=len&&s[i+k]==s[j+k]) k++;
            ht[rk[i]]=k;
        }
    }
}using namespace SA;

int solve(string s){
    getsa(s);
    s[top=1]=1;
    memset(L,0,sizeof(L));
    memset(R,0,sizeof(R));
    sta[top=0]=0;
        for(int i=1;i<=len;i++){
            while(top&&ht[sta[top]]>ht[i]) top--;
            L[i]=sta[top];
            sta[++top]=i;
        }
        sta[top=0]=len+1;
        for(int i=len;i>=1;i--){
            while(top&&ht[sta[top]]>=ht[i]) top--;
            R[i]=sta[top];
            sta[++top]=i;
        }
    int ret=0;
    for(int i=2;i<=len;i++){
        ret+=(R[i]-i)*(i-L[i])*ht[i];
    }
    return ret;
}

signed main(){
    cin>>s1>>s2;
    cout<<solve(s1+"#"+s2)-solve(s1)-solve(s2);
    return 0;
}
