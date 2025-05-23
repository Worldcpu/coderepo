#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7;
int n,top,tot,ans,a[MN],b[MN],pos[MN],pre[MN],nxt[MN],s[MN],fnxt[MN],fpre[MN],cnt[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,sum[4],tg[2];
        //mn,mx,mx*mn,(l-1)*mn;
    }t[MN<<2];

    void pushup(int p){
        for(int i=0;i<4;i++){
            t[p].sum[i]=(t[ls].sum[i]+t[rs].sum[i])%MOD;
        }
    }

    void doit(int p,int v,int op){
        t[p].sum[2]=t[p].sum[op^1]*v%MOD;
        t[p].sum[op]=v*(t[p].r-t[p].l+1)%MOD;
        if(!op) t[p].sum[3]=(1ll*(t[p].l+t[p].r)*(t[p].r-t[p].l+1)/2%MOD)*v%MOD;
        t[p].tg[op]=v;
    }

    void pushdown(int p){
        for(int i=0;i<2;i++){
            if(!t[p].tg[i]) continue;
            doit(ls,t[p].tg[i],i);
            doit(rs,t[p].tg[i],i);
            t[p].tg[i]=0;
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

    void update(int p,int fl,int fr,int op,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doit(p,k,op);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) update(ls,fl,fr,op,k);
        if(mid<fr) update(rs,fl,fr,op,k);
        pushup(p);
    }

    int query(int p,int fl,int fr,int op){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].sum[op];
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=query(ls,fl,fr,op);
        if(mid<fr) ret+=query(rs,fl,fr,op);
        return ret;
    }

#undef ls
#undef rs
}sg;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
        pre[i]=pos[a[i]]+1;
        pos[a[i]]=i;
    }
    for(int i=1;i<=n;i++) pos[i]=n+1;
    for(int i=n;i>=1;i--){
        nxt[i]=pos[a[i]]-1;
        pos[a[i]]=i;
    }
    top=0;
    for(int i=n;i>=1;i--){
        while(top&&pre[s[top]]<pre[i]) top--;
        fpre[i]=top?s[top]:n+1;
        s[++top]=i;
    }
    top=0;
    for(int i=n;i>=1;i--){
        while(top&&nxt[s[top]]>nxt[i]) top--;
        fnxt[i]=top?s[top]:n+1;
        s[++top]=i;
    }
    for(int i=1;i<=n;i++){
        cerr<<fpre[i]<<" "<<pre[i]<<'\n';
    }
    sg.build(1,1,n);
    int l=n,r=n;
    for(l=n;l>=1;l--){
        if(l<fpre[l]){
            sg.update(1,l,fpre[l]-1,0,pre[l]);
        }
        if(l<fnxt[l]){
            sg.update(1,l,fnxt[l]-1,1,nxt[l]);
        }
        ++cnt[a[l]];
        while(cnt[a[l]]>1) --cnt[a[r--]];
        ans=(ans+sg.query(1,l,r,1)*l%MOD)%MOD;
        ans=(ans+sg.query(1,l,r,3))%MOD;
        ans=(ans-sg.query(1,l,r,2))%MOD;
        ans=(ans-1ll*l*(1ll*(l+r)*(r-l+1)/2%MOD))%MOD;
    }
    cout<<(ans+MOD)%MOD;
    return 0;
}
