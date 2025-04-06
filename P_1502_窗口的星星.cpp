#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;

struct scanline{
    ll l,r,h,val;
}line[MN<<2];

struct segtree{
    ll l,r;
    ll sum,add;
}t[MN<<2];

ll zy[MN<<2];
int T,n,W,H;

void init(){
    memset(line,0,sizeof(line));
}

void pushup(ll p){
    t[p].sum=max(t[ls].sum,t[rs].sum);
}

void build(ll p,ll l,ll r){
    t[p].l=l;
    t[p].r=r;
    t[p].sum=t[p].add=0;
    if(l==r){
        return;
    }
    ll mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

void pushdown(ll p){
    if(t[p].add){
        t[ls].add+=t[p].add;
        t[rs].add+=t[p].add;
        t[ls].sum+=t[p].add;
        t[rs].sum+=t[p].add;
        t[p].add=0;
    }
}

void update(ll p,ll fl,ll fr,ll k){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].add+=k;
        t[p].sum+=k;
        return;
    }
    pushdown(p);
    ll mid=t[p].l+t[p].r>>1;
    if(mid>=fl) update(ls,fl,fr,k);
    if(mid<fr) update(rs,fl,fr,k);
    pushup(p);
}

bool cmp(scanline x,scanline y){
    if(x.h==y.h) return x.val>y.val;
    return x.h<y.h;
}

int main(){
    cin>>T;
    while (T--)
    {
        init();
        cin>>n>>W>>H;
        for(int i=1;i<=n;i++){
            ll x,y,lig;
            cin>>x>>y>>lig;
            zy[i*2-1]=y;
            zy[i*2]=y+H-1;
            line[i*2-1]={y,y+H-1,x,lig};
            line[i*2]={y,y+H-1,x+W-1,-lig};
        }
        n<<=1;
        sort(line+1,line+1+n,cmp);
        sort(zy+1,zy+1+n);
        ll m=unique(zy+1,zy+1+n)-zy-1;
        for(int i=1;i<=n;i++){
            line[i].l=lower_bound(zy+1,zy+1+m,line[i].l)-zy;
            line[i].r=lower_bound(zy+1,zy+1+m,line[i].r)-zy;
        }
        build(1,1,m);
        ll ans=0;
        for(int i=1;i<=n;i++){
            update(1,line[i].l,line[i].r,line[i].val);
            ans=max(ans,t[1].sum);
        }
        cout<<ans<<'\n';
    }

    return 0;
}