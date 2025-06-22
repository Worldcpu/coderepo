#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=8e5+15;
struct Query{
    int l,r;
}qry[MN];
int n,q,ans[MN],h[MN],st[MN][30],arcst[MN][30],lg[MN];
vector<int> pos[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r,cov,k,b,lmx,rmx;
    }t[MN<<2];

    void docov(int p){
        t[p].cov=1;
        t[p].k=t[p].b=t[p].lmx=t[p].rmx=0;
    }

    void doadd(int p,int k,int b){
        t[p].k+=k;
        t[p].b+=b;
        t[p].lmx+=k*t[p].l+b;
        t[p].rmx+=k*t[p].r+b;
    } 

    void pushdown(int p){
        if(t[p].cov){
            docov(ls);
            docov(rs);
        }
        if(t[p].k||t[p].b){
            doadd(ls,t[p].k,t[p].b);
            doadd(rs,t[p].k,t[p].b);
        }
        t[p].cov=t[p].k=t[p].b=0;
    }

    void pushup(int p){
        t[p].lmx=t[ls].lmx,t[p].rmx=t[rs].rmx;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,0,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) update(ls,fl,fr,k);
        if(mid<fr) update(rs,fl,fr,k);
        pushup(p);
    }

    void merge(int p,int fl,int fr,int k,int b){
        if(t[p].l>=fl&&t[p].r<=fr){
            int lv=t[p].l*k+b,rv=k*t[p].r+b;
            if(lv>=t[p].lmx&&t[p].rmx<=rv) return;
            if(t[p].lmx>=lv&&rv<=t[p].rmx){
                docov(p);
                doadd(p,k,b);
                return;
            }
        }  
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) merge(ls,fl,fr,k,b);
        if(mid<fr) merge(rs,fl,fr,k,b);
        pushup(p);
    }

    int querylmx(int p,int pos){
        if(t[p].l==t[p].r) return t[p].lmx;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return querylmx(ls,pos);
        return querylmx(rs,pos);
    }

    int queryrmx(int p,int pos){
        if(t[p].l==t[p].r) return t[p].rmx;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return queryrmx(ls,pos);
        else return queryrmx(rs,pos);
    }
#undef ls
#undef rs
}s,t;

void initst(){
    for(int j=1;j<=20;j++){
        for(int i=1;i<=n;i++){
            if(i+(1<<j)-1>n) break;
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            if(st[i][j]==st[i][j-1]) arcst[i][j]=arcst[i][j-1];
            else arcst[i][j]=arcst[i+(1<<(j-1))][j-1];
        }
    }
}

int cmp(int l,int r){
    int len=__lg(r-l+1);
    if(st[l][len]>=st[r-(1<<len)+1][len]){
        return arcst[l][len];
    }else return arcst[r-(1<<len)+1][len];
}

void solve(int l,int r){
    if(l>r) return;
    int mid=cmp(l,r);
    solve(l,mid-1);
    solve(mid+1,r);
    for(auto now:pos[mid]){
        ans[now]=h[mid]*(qry[now].r-qry[now].l+1);
        if(qry[now].l<mid){
            ans[now]=min(ans[now],s.querylmx(1,qry[now].l)+h[mid]*(qry[now].r-mid+1));
        }
        if(qry[now].r>mid){
            ans[now]=min(ans[now],t.queryrmx(1,qry[now].r)+h[mid]*(mid-qry[now].l+1));
        }
    }

    int sx=h[mid],tx=h[mid];
    if(l<mid) tx+=t.queryrmx(1,mid-1);
    if(r>mid) sx+=s.queryrmx(1,mid+1);
    s.update(1,mid,mid,sx);
    t.update(1,mid,mid,tx);
    if(l<mid){
        s.update(1,l,mid-1,h[mid]*(r-mid+1));
        s.merge(1,l,mid-1,-1*h[mid],sx+mid*h[mid]);
    }
    if(r>mid){
        t.update(1,mid+1,r,h[mid]*(mid-l+1));
        t.merge(1,mid+1,r,1ll*h[mid],tx-1ll*mid*h[mid]);
    }

}

signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        st[i][0]=h[i];
        arcst[i][0]=i;
    }
    for(int i=1;i<=q;i++){
        cin>>qry[i].l>>qry[i].r;
        qry[i].l++;
        qry[i].r++;
    }
    initst();
    for(int i=1;i<=q;i++){
        pos[cmp(qry[i].l,qry[i].r)].push_back(i);
    }
    s.build(1,1,n);
    t.build(1,1,n);
    solve(1,n);
    for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
    return 0;
}
