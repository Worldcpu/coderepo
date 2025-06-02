#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,m,a[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,hadd,hsum,hcnt,sum,add;
    }t[MN<<2];

    void doadd(int p,int v){
        t[p].sum+=(t[p].r-t[p].l+1)*v;
        t[p].add+=v;
    }

    void dohadd(int p,int cnt,int v){
        t[p].hcnt+=cnt;
        t[p].hsum+=(t[p].r-t[p].l+1)*v+t[p].sum*cnt;
        t[p].hadd+=t[p].add*cnt+v;
    }

    void pushup(int p){
        t[p].sum=t[ls].sum+t[rs].sum;
        t[p].hsum=t[ls].hsum+t[rs].hsum;
    }

    void pushdown(int p){
        dohadd(ls,t[p].hcnt,t[p].hadd);
        dohadd(rs,t[p].hcnt,t[p].hadd);
        doadd(ls,t[p].add);
        doadd(rs,t[p].add);
        t[p].add=t[p].hadd=t[p].hcnt=0;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].sum=t[p].hsum=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) update(ls,fl,fr,k);
        if(mid<fr) update(rs,fl,fr,k);
        pushup(p);
    }

    int querysum(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].sum;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=querysum(ls,fl,fr);
        if(mid<fr) ret+=querysum(rs,fl,fr);
        return ret;
    }

    int queryhsum(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].hsum;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=queryhsum(ls,fl,fr);
        if(mid<fr) ret+=queryhsum(rs,fl,fr);
        return ret;
    }

    void updatetime(){
        dohadd(1,1,0);
    }

#undef ls
#undef rs
}sg;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sg.build(1,1,n);
    while(m--){
        int op,l,r,x;
        cin>>op>>l>>r;
        if(op==1){
            cin>>x;
            sg.update(1,l,r,x);
        }else{
            cout<<sg.queryhsum(1,l,r)<<'\n';
        }
        sg.updatetime();
    }
    return 0;
}
