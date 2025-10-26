#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
constexpr ull base=13131,MOD=100000217;
int n,m,res,ans;
string s,t;
ull hshs[MN],hsht[MN],pw[MN];
vector<int> lcp[MN],lcs[MN];

struct BIT{
    int t[MN];
    int lowbit(int x){return x&-x;}
    void modify(int x,int k){while(x<MN){t[x]+=k;x+=lowbit(x);}}
    int query(int x){int ret=0;while(x>0){ret+=t[x];x-=lowbit(x);}return ret;}
    int query(int l,int r){if(l>r)return 0;return query(r)-query(l-1);}
}tf,tg;

ull gethsh(ull hsh[],int l,int r){
    return (hsh[r]-hsh[l-1]*pw[r-l+1]%MOD+MOD)%MOD;
}

void changef(int pos,int k){
    tf.modify(pos,k);
    int r=pos-m;
    if(r<1)r=0;
    res+=tg.query(1,r)*k;
}

void changeg(int pos,int k){
    tg.modify(pos,k);
    int l=pos+m;
    if(l>n)l=n+1;
    res+=tf.query(l,n)*k;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>s>>t;
    n=s.length(),m=t.length();
    s=" "+s,t=" "+t;
    for(int i=1;i<=n;i++)hshs[i]=(hshs[i-1]*base+s[i])%MOD;
    for(int i=1;i<=m;i++)hsht[i]=(hsht[i-1]*base+t[i])%MOD;
    pw[0]=1;
    for(int i=1;i<=max(n,m);i++)pw[i]=pw[i-1]*base%MOD;
    for(int i=1;i<=n;i++){
        int l=1,r=min(m,n-i+1),ret=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(gethsh(hshs,i,i+mid-1)==gethsh(hsht,1,mid))l=mid+1,ret=mid;
            else r=mid-1;
        }
        lcp[ret].push_back(i);
    }
    for(int i=1;i<=n;i++){
        int l=1,r=min(m,i),ret=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(gethsh(hshs,i-mid+1,i)==gethsh(hsht,m-mid+1,m))l=mid+1,ret=mid;
            else r=mid-1;
        }
        lcs[m-ret+1].push_back(i);
    }
    for(int i=0;i<=m;i++)
        for(auto p:lcp[i])changeg(p,1);
    for(auto p:lcs[1])changef(p,1);
    for(int i=1;i<m;i++){
        for(auto p:lcp[i-1])changeg(p,-1);
        for(auto p:lcs[i+1])changef(p,1);
        ans+=res;
    }
    for(int i=1;i<=n-m+1;i++){
        if(gethsh(hshs,i,i+m-1)==gethsh(hsht,1,m)){
            int x=i,y=i+m-1;
            ans+=(n-y+1)*(n-y)/2;
            ans+=x*(x-1)/2;
        }
    }
    cout<<ans;
    return 0;
}
