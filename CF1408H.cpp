#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,sum[MN],L[MN],R[MN],tg[MN],a[MN],sum0,ctot,lim,ans;

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
            t[p].mn=l+ctot;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
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

    void addall(int k){
        add(1,0,lim,k);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mn;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=1e9;
        if(mid>=fl) ret=min(ret,query(ls,fl,fr));
        if(mid<fr) ret=min(ret,query(rs,fl,fr));
        return ret;
    }

    int queryall(){
        return query(1,0,lim);
    }
}sg;

void init(){
    ans=ctot=m=0;
    for(int i=1;i<=n;i++){
        L[i]=R[i]=sum[i]=tg[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+(!a[i]);
    }
    m=sum[n]>>1;
    lim=sum[n]-m;
    for(int i=1;i<=n;i++){
        if(sum[i]<=m){
            tg[i]=1;
        }else tg[i]=2;
    }
    for(int i=1;i<=n;i++){
        if(tg[i]==1&&a[i]){
            L[a[i]]=i;
        }
    }
    for(int i=n;i>=1;i--){
        if(tg[i]==2&&a[i]) R[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        ctot+=(L[i]||R[i]);
    }
    sg.build(1,0,lim);
    for(int i=1;i<=n;i++){
        if(!L[i]&&R[i]){
            sg.add(1,sum[n]-sum[R[i]-1],lim,-1);
        }
    }
    ans=min(m,sg.queryall());
    for(int i=1;i<=n&&tg[i]==1;i++){
        if(L[a[i]]==i){
            if(R[a[i]]){
                sg.add(1,sum[n]-sum[R[a[i]]-1],lim,-1);
            }else{
                sg.addall(-1);
            }
            ans=min(ans,sg.queryall()+sum[i]);
        }
    }
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}