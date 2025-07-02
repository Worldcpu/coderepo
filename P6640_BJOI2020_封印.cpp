#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int q,n,m;
string s,t,st;

namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],ST[30][MN];

    void getsa(string s){
        int m=400000;
        len=s.length();
        s=" "+s;
        for(int i=1;i<=len;i++){
            x[i]=s[i];
            c[x[i]]++;
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
            for(int i=len;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
            swap(x,y);
            num=x[sa[1]]=1;
            for(int i=2;i<=len;i++){
                if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) x[sa[i]]=num;
                else x[sa[i]]=++num;
            }
            if(num==len) break;
            m=num;
        }
        for(int i=1;i<=len;i++) rk[sa[i]]=i;
#ifdef SAONE
        for(int i=1,k=0;i<=len;i++){
          ht[rk[i]] = max(ht[rk[i - 1]] - 1, 0);
            while (s[i + ht[rk[i]]] == s[sa[rk[i] - 1] + ht[rk[i]]]) 
                ht[rk[i]]++;
        }
#endif
#ifndef SAONE
        for(int i=1,k=0;i<=len;i++){
            if(rk[i]==1) continue;
            if(k) k--;
            int j=sa[rk[i]-1];
            while(i+k<=len&&j+k<=len&&s[i+k]==s[j+k]) k++;
            ht[rk[i]]=k;
        }
#endif
        for(int i=1;i<=len;i++) cerr<<ht[i]<<" ";
    }

    void initst(){
        int minn=0x3f3f3f3f;
        for(int i=2;i<=len;i++){
            minn=min(minn,ht[i]);
            if(sa[i]>m+1){
                ST[0][sa[i]-1-m]=minn;
            }else minn=ht[i+1];
        }
        minn=0x3f3f3f3f;
        for(int i=len;i>=1;i--){
            minn=min(minn,ht[i+1]);
            if(sa[i]>m+1){
                ST[0][sa[i]-1-m]=max(ST[0][sa[i]-1-m],minn);
            }else minn=ht[i];
        }
        for(int i=1;i<30;i++){
            for(int j=1;j+(1<<i-1)<=len;j++){
                ST[i][j]=max(ST[i-1][j],ST[i-1][j+(1<<i-1)]);
            }
        }
    }

}using namespace SA;

int query(int l,int r){
    if(l>r) return 0;
    int lg=__lg(r-l+1);
    return max(ST[lg][l],ST[lg][r-(1<<lg)+1]);
}

int solve(int l,int r){
    int L=0,R=r-l+2;
    while(L+1<R){
        int mid=(L+R)>>1;
        if(query(l,r-mid+1)>=mid) L=mid;
        else R=mid;
    }
    return L;
}

int main(){
    cin>>s>>t>>q;
    n=s.length(),m=t.length();
    st=t+'#'+s;
    cerr<<st<<'\n';
    getsa(st);
    initst();
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<solve(l,r)<<'\n';
    }
    return 0;
}
