#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int a[MN],n,q,ql[MN],qr[MN],ans[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mn,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].mn=min(t[ls].mn,t[rs].mn);
    }

    void doadd(int p,int k){
        t[p].mn+=k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].add=0;
        if(l==r){
            t[p].mn=0;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void add(int p,int fl,int fr,int k){
        if(fl>fr) return;
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

    int query(int p,int fl,int fr){
        if(fl>fr) return INF;
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mn;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=INF;
        if(mid>=fl) ret=min(ret,query(ls,fl,fr));
        if(mid<fr) ret=min(ret,query(rs,fl,fr));
        return ret;
    }

    #undef ls
    #undef rs
}sgmn;

struct SegmentMX{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int mx,pos;

        Node(int mxx=0,int poss=0){
            mx=mxx,pos=poss;
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.mx=max(x.mx,y.mx);
            if(ret.mx!=x.mx) ret.pos=y.pos;
            else if(ret.mx!=y.mx) ret.pos=x.pos;
            else ret.pos=min(x.pos,y.pos);
            return ret;
        }
    };

    struct SNode{
        int l,r;
        Node val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=Node(a[l],l);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    

    Node query(int p,int fl,int fr){
        if(fl>fr) return Node(0,0);
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fr) return query(ls,fl,fr);
        if(mid<fl) return query(rs,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }

    #undef ls
    #undef rs
}sgmx;

namespace SOLVE{
    int st[MN],top;
    vector<pir> pos[MN];

    void init(){
        top=0;
        sgmn.build(1,1,n);
        sgmx.build(1,1,n);
        for(int i=1;i<=n;i++){
            pos[i].clear();
        }
        for(int i=1;i<=q;i++){
            pos[qr[i]].push_back(pir(ql[i],i));
        }
    }

    void solve1(){
        for(int i=1;i<=n;i++){
            while(top&&a[i]>=a[st[top]]){
                sgmn.add(1,st[top-1],st[top]-1,a[i]-a[st[top]]);
                top--;
            }
            st[++top]=i;
            if(i>1) sgmn.add(1,i-1,i-1,a[i]+a[i-1]);
            for(auto p:pos[i]){
                auto ret=sgmx.query(1,p.first,i);               
                if(ret.pos+1<=i-1){
                    ans[p.second]=min(ans[p.second],ret.mx+sgmn.query(1,ret.pos+1,i-1));
                }
            }
        }
    }

    void solve2(){
        for(int i=1;i<=q;i++){
            ans[i]=min(ans[i],a[ql[i]]+a[qr[i]]+sgmx.query(1,ql[i]+1,qr[i]-1).mx);
        }
    }

    void solve(){
        init();
        solve1();
        solve2();
    }
}

signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=q;i++){
        cin>>ql[i]>>qr[i];
    }
    memset(ans,0x3f,sizeof(ans));
    SOLVE::solve();
    
    reverse(a+1,a+1+n);
    for(int i=1;i<=q;i++){
        int qwq=ql[i],pwp=qr[i];
        ql[i]=n-pwp+1;
        qr[i]=n-qwq+1;
    
    }
    SOLVE::solve();
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}