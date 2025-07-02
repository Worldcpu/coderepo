#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15,MK=35;
int f[MN][MK],X,n,m;
string s,t,sst;


namespace SA{
    int len,sa[MN],x[MN],y[MN],rk[MN],c[MN],ht[MN],st[30][MN];

    void getsa(string s){
        int m=1<<7,p=0;
        len=s.length();
        s=" "+s;
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
            ht[rk[i]]=st[0][rk[i]]=k;
        }
    }

    void initst(){
        for(int i=1;i<30;i++){
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

    int queryst(int l,int r){
        int d=__lg(r-l+1);
        return min(st[d][l],st[d][r-(1<<d)+1]);
    }

}using namespace SA;

int lcpst(int i,int j){
    if(i>n||j>m) return 0;
    j+=n+1;
    return lcp(i,j);
}

int main(){
    cin>>n>>s>>m>>t;
    sst=s+'#'+t;
    getsa(sst);
    initst();
    cin>>X;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=X;j++){
            int L=lcpst(i,f[i][j-1]+1);
            f[i+L][j]=max(f[i+L][j],f[i][j-1]+L);
            f[i+1][j]=max(f[i+1][j],f[i][j]);
        }
    }
    if(f[n+1][X]==m) cout<<"YES";
    else cout<<"NO";
    return 0;
}
