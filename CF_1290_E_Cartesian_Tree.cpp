#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int n,a[MN],ans[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mx,cmx,mxcnt,sum,add,len;
    }t[MN<<2];

    void pushup(int p){
        t[p].mxcnt=0;
        t[p].cmx=-INF;

        t[p].mx=max(t[ls].mx,t[rs].mx);
        t[p].sum=t[ls].sum+t[rs].sum;
        t[p].len=t[ls].len+t[rs].len;

        if(t[p].mx==t[ls].mx){
            t[p].mxcnt+=t[ls].mxcnt;
        }
        if(t[p].mx==t[rs].mx){
            t[p].mxcnt+=t[rs].mxcnt;
        }

        if(t[p].mx==t[ls].mx&&t[p].mx==t[rs].mx){
            t[p].cmx=max(t[ls].cmx,t[rs].cmx);
        }else if(t[p].mx==t[ls].mx){
            t[p].cmx=max(t[ls].cmx,t[rs].mx);
        }else if(t[p].mx==t[rs].mx){
            t[p].cmx=max(t[ls].mx,t[rs].cmx);
        }
    }

    void doadd(int p,int k){
        t[p].sum+=t[p].len*k;
        t[p].mx+=k;
        t[p].add+=k;
        if(t[p].cmx!=-INF){
            t[p].cmx+=k;
        }
    }

    void domx(int p,int k){
        if(t[p].mx<=k) return;
        t[p].sum-=(t[p].mx-k)*t[p].mxcnt;
        t[p].mx=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
        domx(ls,t[p].mx);
        domx(rs,t[p].mx);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].mx=t[p].mxcnt=t[p].sum=t[p].add=t[p].len=0;
        t[p].cmx=-INF;
        if(l==r){
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void add(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) add(ls,fl,fr,k);
        if(mid<fr) add(rs,fl,fr,k);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].len=t[p].mxcnt=1;
            t[p].mx=t[p].sum=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    void modifymx(int p,int fl,int fr,int k){
        if(t[p].mx<=k) return;
        if(t[p].l>=fl&&t[p].r<=fr&&t[p].cmx<k){
            domx(p,k);
            return;
        }
        if(t[p].l==t[p].r) return;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifymx(ls,fl,fr,k);
        if(mid<fr) modifymx(rs,fl,fr,k);
        pushup(p);
    }

    int querylen(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].len;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=querylen(ls,fl,fr);
        if(mid<fr) ret+=querylen(rs,fl,fr);
        return ret;
    }

}sg;

void solve(){
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        sg.add(1,a[i]+1,n,1);
        int lenn=sg.querylen(1,a[i]+1,n);
        sg.modify(1,a[i],i+1);
        sg.modifymx(1,1,a[i]-1,i-lenn);
        ans[i]+=sg.t[1].sum;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[x]=i;
    }
    solve();
    for(int i=1;i<=n;i++) a[i]=n-a[i]+1;
    solve();
    for(int i=1;i<=n;i++){
        cout<<ans[i]-i*(i+2)<<'\n';
    }

    return 0;
}