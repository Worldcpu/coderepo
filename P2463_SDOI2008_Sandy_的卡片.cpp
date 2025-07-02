#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,lenn[MN],sta[MN],top,a[1145][1145];
int pos[MN];
bool vis[MN];
string s;

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

bool check(int x){
    while(top) vis[sta[top--]]=0;
    for(int i=1;i<=len;i++){
        if(ht[i]<x) while(top) vis[sta[top--]]=0;
        if(!vis[pos[sa[i]]]){
            vis[pos[sa[i]]]=1;
            sta[++top]=pos[sa[i]];
            if(top==n) return 1;
        }
    }
    return 0;
}

int main(){
    cin>>n;
    int l=0,r=1e6,ans=0;
    for(int i=1;i<=n;i++){
        cin>>lenn[i];
        for(int j=1;j<=lenn[i];j++){
            cin>>a[i][j];
        }
        r=min(r,lenn[i]-1);
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=lenn[i];j++){
            s.push_back(a[i][j]-a[i][j-1]);
            pos[s.length()]=i;
        }
        s.push_back('#');
    }
    getsa(s);
    
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            l=mid+1;
            ans=mid;
        }else r=mid-1;
    }
    cout<<ans+1;
    return 0;
}
