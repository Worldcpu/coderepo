#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int T,n,q,top1,top2,a[MN],b[MN],s1[MN],s2[MN];
ull ans[MN];
vector<pir> qry[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        ull l,r,hsum,sum,suma,sumb,adda,addb,hadda,haddb,haddab,hcnt;
    }t[MN<<2];

    void doadd(int p,int va,int vb){
        t[p].sum+=t[p].sumb*va;
        t[p].suma+=(t[p].r-t[p].l+1)*va;
        t[p].adda+=va;
        t[p].sum+=t[p].suma*vb;
        t[p].sumb+=(t[p].r-t[p].l+1)*vb;
        t[p].addb+=vb;
    }

    void dohadd(int p,int cnt,int va,int vb,int vab){
        t[p].hsum+=t[p].sum*cnt+t[p].suma*vb+t[p].sumb*va+vab*(t[p].r-t[p].l+1);
        t[p].hcnt+=cnt;
        t[p].hadda+=t[p].adda*cnt+va;
        t[p].haddb+=t[p].addb*cnt+vb;
        t[p].haddab+=t[p].adda*t[p].addb*cnt+t[p].adda*vb+t[p].addb*va+vab;
    }

    void pushup(int p){
        t[p].sum=t[ls].sum+t[rs].sum;
        t[p].suma=t[ls].suma+t[rs].suma;
        t[p].sumb=t[ls].sumb+t[rs].sumb;
        t[p].hsum=t[ls].hsum+t[rs].hsum;
    }

    void pushdown(int p){
        dohadd(ls,t[p].hcnt,t[p].hadda,t[p].haddb,t[p].haddab);
        dohadd(rs,t[p].hcnt,t[p].hadda,t[p].haddb,t[p].haddab);
        doadd(ls,t[p].adda,t[p].addb);
        doadd(rs,t[p].adda,t[p].addb);
        t[p].adda=t[p].addb=t[p].hadda=t[p].haddb=t[p].haddab=t[p].hcnt=0;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modifya(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k,0);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifya(ls,fl,fr,k);
        if(mid<fr) modifya(rs,fl,fr,k);
        pushup(p);
    }

    void modifyb(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,0,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifyb(ls,fl,fr,k);
        if(mid<fr) modifyb(rs,fl,fr,k);
        pushup(p);
        
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].hsum;
        }
        pushdown(p);
        int ret=0,mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) ret+=query(ls,fl,fr);
        if(mid<fr) ret+=query(rs,fl,fr);
        return ret;
    }

    void upd(){
        dohadd(1,1,0,0,0);
    }

#undef ls
#undef rs
}sg;


signed main(){
    cin>>T>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        qry[r].push_back(pir(l,i));
    }
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        while(top1&&a[i]>a[s1[top1]]){
            sg.modifya(1,s1[top1-1]+1,s1[top1],-a[s1[top1]]);
            top1--;
        }
        sg.modifya(1,s1[top1]+1,i,a[i]);
        while(top2&&b[i]>b[s2[top2]]){
            sg.modifyb(1,s2[top2-1]+1,s2[top2],-b[s2[top2]]);
            top2--;
        }
        sg.modifyb(1,s2[top2]+1,i,b[i]);
        sg.upd();
        s1[++top1]=i;
        s2[++top2]=i;
        for(auto p:qry[i]){
            ans[p.second]=sg.query(1,p.first,i);
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}
