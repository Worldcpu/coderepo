#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
constexpr int MOD=998244353;
int n,m,q;
vector<int> pr[MN];
bool vis[MN];
int bx[MN];

struct segtree1{
    #define ls p<<1
    #define rs p<<1|1

    struct{
        int l,r,c,s1,s2;
        bool rev;
    }t[MN<<2];

    void pushup(int p){
        t[p].c=t[ls].c+t[rs].c;
        t[p].s1=(t[ls].s1+t[rs].s1)%MOD;
        t[p].s2=(1ll*t[ls].s1*t[rs].c+t[ls].s2+t[rs].s2)%MOD;
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

    void update(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].c+=k;
            t[p].s1=1ll*(t[p].c*pos)%MOD;
            t[p].s2=1ll*pos*(t[p].c+1)*t[p].c/2%MOD;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) update(ls,pos,k);
        else update(rs,pos,k);
        pushup(p);
    }

    #undef ls
    #undef rs
}sg;

struct segtree2{
    #define ls p<<1
    #define rs p<<1|1
    private:

        int s[MN],top;
        struct{
            int l,r,s0,s1,col,fl;
            int dotag,doswp,covnum;
        }t[MN<<2];
    
    public:

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].s0=r-l+1;
        t[p].fl=1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }
    
    void pushdown(int p){
        if(t[p].dotag){
            t[ls].dotag=t[rs].dotag=t[ls].fl=t[rs].fl=1;
            if(t[p].doswp){
                swap(t[ls].s0,t[ls].s1);
                swap(t[rs].s0,t[rs].s1);
                t[ls].doswp^=1;
                t[rs].doswp^=1;
            }
            t[ls].covnum=t[rs].covnum=t[ls].col=t[rs].col=t[p].covnum;
            t[p].covnum=t[p].dotag=t[p].doswp=0;
        }
    }

    void pushup(int p){
        t[p].s0=t[ls].s0+t[rs].s0;
        t[p].s1=t[ls].s1+t[rs].s1;
        if(!t[ls].fl || !t[rs].fl) t[p].fl=0;
        if(t[ls].col==t[rs].col|| !t[ls].col || !t[rs].col){
            t[p].fl=1;
            t[p].col=t[ls].col | t[rs].col;
        }else t[p].fl=0;
    }

    void change(int p,int k){
        if(!vis[p]){
            vis[p]=1;
            s[++top]=p;
        }
        bx[p]+=k;
    }

    void add(int p,int k){
        change(t[p].col,-t[p].s1);
        swap(t[p].s0,t[p].s1);
        t[p].dotag=1;
        t[p].doswp^=1;
        t[p].col=t[p].covnum=k;
        if(!t[p].s1){
            t[p].covnum=t[p].col=0;
        }else change(k,t[p].s1);
    }

    void rever(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr&&t[p].fl){
            return add(p,k);
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) rever(ls,fl,fr,k);
        if(mid<fr) rever(rs,fl,fr,k);
        pushup(p);
    }

    void updateseg1(){
        while(top){
            sg.update(1,s[top],bx[s[top]]);
            vis[s[top]]=bx[s[top]]=0;
            top--;
        }
    }

    #undef ls
    #undef rs
}seg;

int main(){
    // #ifndef ONLINE_JUDTE
    // freopen("gothic.in","r",stdin);
    // freopen("gothic.out","w",stdout);
    // #endif
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++){
        int x,y,l,r;
        cin>>x>>y>>l>>r;
        pr[x].push_back(l);
        pr[x].push_back(r+1);
        pr[y+1].push_back(l);
        pr[y+1].push_back(r+1);
    }
    seg.build(1,1,m);
    sg.build(1,1,n);
    int ans=0;
    for(int i=1;i<=m;i++){
        sort(pr[i].begin(),pr[i].end());
        for(int j=0;j+1<pr[i].size();j+=2){
            int x=pr[i][j],y=pr[i][j+1]-1;
            if(x<=y){
                seg.rever(1,x,y,i);
            }
        }
        seg.updateseg1();
        int c=m-sg.t[1].c,s1=sg.t[1].s1,s2=sg.t[1].s2;
        ans=(ans+1ll*(i+1)*m*(m+1)/2%MOD)%MOD;
        ans=(ans-s2+MOD)%MOD;
        ans=(ans-1ll*s1*c%MOD+MOD)%MOD;
        ans=(ans-1ll*(i+1)*c*(c+1)/2%MOD+MOD)%MOD;
    }
    cout<<ans;
    return 0;
}