#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15,INF=1e18;
int n,m,q,c[MN],ans[MN];
bool isfind[MN];
vector<pir> qry[MN],chaf[MN];

struct Segment1{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,mx,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
    }

    void pushdown(int p){
        if(t[p].add){
            t[ls].add+=t[p].add;
            t[rs].add+=t[p].add;
            t[ls].mx+=t[p].add;
            t[rs].mx+=t[p].add;
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l,t[p].r=r;
        if(l==r){
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    int query(int p,int pos){
        if(t[p].l==t[p].r) return t[p].mx;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return query(ls,pos);
        else return query(rs,pos);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            t[p].add+=k;
            t[p].mx+=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    int find(int p,int k){
        if(t[p].mx<k) return 0;
        if(t[p].l==t[p].r) return t[p].l;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(t[ls].mx>=k) return find(ls,k);
        else return find(rs,k);
    }

#undef ls
#undef rs
}sg1,sg2;

struct Segment2{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,mx,tagadd,tagmx;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].tagmx=-INF;
        if(l==r){
            t[p].mx=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void pushdown(int p){
        if(t[p].tagadd){
            t[ls].tagadd+=t[p].tagadd;
            t[rs].tagadd+=t[p].tagadd;
            t[ls].mx+=t[p].tagadd;
            t[rs].mx+=t[p].tagadd;
            if(t[ls].tagmx!=-INF) t[ls].tagmx+=t[p].tagadd;
            if(t[rs].tagmx!=-INF) t[rs].tagmx+=t[p].tagadd;
            t[p].tagadd=0;
        }
        if(t[p].tagmx!=-INF){
            t[ls].tagmx=max(t[ls].tagmx,t[p].tagmx);
            t[rs].tagmx=max(t[rs].tagmx,t[p].tagmx);
            t[ls].mx=max(t[ls].mx,t[p].tagmx);
            t[rs].mx=max(t[rs].mx,t[p].tagmx);
            t[p].tagmx=-INF;
        }
    }

    void modifyadd(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            t[p].tagadd+=k;
            t[p].mx+=k;
            if(t[p].tagmx!=-INF) t[p].tagmx+=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifyadd(ls,fl,fr,k);
        if(mid<fr) modifyadd(rs,fl,fr,k);
        pushup(p);
    }

    void modifymx(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            t[p].tagmx=max(t[p].tagmx,k);
            t[p].mx=max(t[p].mx,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifymx(ls,fl,fr,k);
        if(mid<fr) modifymx(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int pos){
        if(t[p].l==t[p].r){
            return t[p].mx;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return query(ls,pos);
        else return query(rs,pos);
    }

#undef ls
#undef rs
}sg3;

signed main(){
    memset(ans,-1,sizeof(ans));
    cin>>n>>m>>q;
    sg1.build(1,1,n);
    sg2.build(1,1,q);
    sg3.build(1,1,n);
    for(int i=1;i<=q;i++){
        int op,l,r,k,a,b;
        cin>>op;
        if(op==1){
            cin>>l>>r>>c[i]>>k;
            sg1.modify(1,l,r,k);
            sg3.modifyadd(1,l,r,k);
            chaf[l].push_back(pir(k,i));
            chaf[r+1].push_back(pir(-k,i));
        }
        if(op==2){
            cin>>l>>r>>k;
            sg3.modifyadd(1,l,r,-k);
            sg3.modifymx(1,l,r,0);
        }
        if(op==3){
            cin>>a>>b;
            qry[a].push_back(pir(b+sg1.query(1,a)-sg3.query(1,a),i));
        }
    }
    for(int i=1;i<=n;i++){
        for(auto p:chaf[i]) sg2.modify(1,p.second,q,p.first);
        for(auto p:qry[i]) ans[p.second]=sg2.find(1,p.first);
    }
    for(int i=1;i<=q;i++){
        if(~ans[i]){
            if(ans[i]>i) cout<<0<<'\n';
            else cout<<c[ans[i]]<<'\n';
        }
    }
    return 0;
}
