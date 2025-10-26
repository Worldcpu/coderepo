#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int h[MN],n,d,r,ans,pos[MN],f[MN];
priority_queue<pir> q;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mx;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mx=-1;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mx;
        }
        int mid=(t[p].l+t[p].r)>>1,mx=-INF;
        if(mid>=fl) mx=max(mx,query(ls,fl,fr));
        if(mid<fr) mx=max(mx,query(rs,fl,fr));
        return mx;
    }

    void modifyval(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].mx=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modifyval(ls,pos,k);
        else modifyval(rs,pos,k);
        pushup(p);
    }
}sg;

signed main(){
    cin>>n>>d>>r;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        q.push(pir(h[i],i));
        pos[h[i]]=i;
    }
    sg.build(1,1,n);
    for(int i=n;i>=1;i--){
        if(i+d<=n){
            sg.modifyval(1,pos[i+d],f[i+d]);
        }
        f[i]=sg.query(1,max(pos[i]-r,1),min(pos[i]+r,n))+1;
    }

    cout<<*max_element(f+1,f+1+n);
    return 0;
}