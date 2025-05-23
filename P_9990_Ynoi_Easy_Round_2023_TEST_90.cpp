#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,ans[MN],a[MN],pre[MN],pos[MN];
vector<pir> q[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,rev,hsum,sum,cnt0,cnt1;
    }t[MN<<2];

    void doit(int p,int cnt0,int cnt1,int op){
        t[p].hsum+=cnt0*t[p].sum+cnt1*(t[p].r-t[p].l+1-t[p].sum);
        if(t[p].rev)  t[p].cnt0+=cnt1,t[p].cnt1+=cnt0;
        else t[p].cnt0+=cnt0,t[p].cnt1+=cnt1;
        if(op) t[p].rev^=1,t[p].sum=t[p].r-t[p].l+1-t[p].sum;
    }

    void pushdown(int p){
        doit(ls,t[p].cnt0,t[p].cnt1,t[p].rev);
        doit(rs,t[p].cnt0,t[p].cnt1,t[p].rev);
        t[p].cnt0=t[p].cnt1=t[p].rev=0;
    }

    void pushup(int p){
        t[p].sum=(t[ls].sum+t[rs].sum);
        t[p].hsum=t[ls].hsum+t[rs].hsum;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].hsum;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=query(ls,fl,fr);
        if(mid<fr) ret+=query(rs,fl,fr);
        return ret;
    }

    void update(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return doit(p,0,0,1);
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) update(ls,fl,fr);
        if(mid<fr) update(rs,fl,fr);
        pushup(p);
    }
#undef ls
#undef rs
}sg;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        pre[i]=pos[a[i]];
        pos[a[i]]=i;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        q[r].push_back(pir(l,i));
    }
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        sg.update(1,pre[i]+1,i);
        sg.doit(1,1,0,0);
        for(auto p:q[i]){
            ans[p.second]=sg.query(1,p.first,i);
        }
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}
