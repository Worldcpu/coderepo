#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f3f3f3f3f;
int n,X,Y,Z,nxt[MN],f[MN];
string s;

struct BIT{
    int t[MN];

    BIT(){
        memset(t,0x3f,sizeof(t));
    }

    int lowbit(int x){return x&-x;}

    void modify(int x,int k){
        while(x){
            t[x]=min(t[x],k);
            x-=lowbit(x);
        }
    }

    int query(int x){
        int ret=INF;
        while(x<MN){
            ret=min(ret,t[x]);
            x+=lowbit(x);
        }
        return ret;
    }

}bit;

void qnxt(string s){
    int l=-1,r=-1;
    nxt[0]=n;
    for(int i=1;i<n;i++){
        if(i<r) nxt[i]=min(nxt[i-l],r-i);
        while(i+nxt[i]<n&&s[i+nxt[i]]==s[nxt[i]]) ++nxt[i];
        if(i+nxt[i]>r){
            l=i;
            r=i+nxt[i];
        }
    }
}

signed main(){
    #ifndef ONLINE_JUDGE
    freopen("edit.in","r",stdin);
    freopen("edit.out","w",stdout);
    #endif
    cin>>s>>X>>Y>>Z;
    n=s.length();
    qnxt(s);
    for(int i=1;i<=n;i++){
        f[i]=min(bit.query(i),X*i);
        if(i%2==0&&nxt[i/2]>=i/2) f[i]=min(f[i],f[i/2]+Y);
        int r=i+min(nxt[i],i-1);
        bit.modify(r, f[i]+Y+Z);
    }
    cout<<f[n];

    return 0;
}