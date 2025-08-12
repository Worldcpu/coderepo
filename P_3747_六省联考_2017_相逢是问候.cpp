#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,ML=40,MB=1e4;
int n,q,MOD,C,ptot,lim[MN],a[MN],c[MN],phi[ML],pw1[ML][MB+5],pw2[ML][20005],pw[31][MN];

struct Segment{
    #define ls (p<<1)
    #define rs (p<<1|1)
    struct Node{
        int l,r,sum,cnt;
    }t[MN<<2];

    int ksm(int a,int b){
        return pw1[b][a%MB]*pw2[b][a/MB]%phi[b];
    }

    int solve(int x,int cnt,int pos){
        if(pos==ptot) return 0;
        if(cnt==0) return a[x]%phi[pos];
        if(C==1||(cnt-1<=lim[x]&&pw[cnt-1][x]<phi[pos+1]))
            return ksm(solve(x,cnt-1,pos+1),pos);
        else
            return ksm(solve(x,cnt-1,pos+1)+phi[pos+1],pos);
    }

    void pushup(int p){
        t[p].sum=(t[ls].sum+t[rs].sum)%MOD;
        t[p].cnt=min(t[ls].cnt,t[rs].cnt);
    }

    void build(int p,int l,int r){
        t[p].l=l; t[p].r=r;
        if(l==r){
            t[p].sum=a[l]%MOD;
            t[p].cnt=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr){
        if(t[p].r<fl||t[p].l>fr||t[p].cnt>=ptot) return;
        if(t[p].l==t[p].r){
            t[p].sum=solve(t[p].l,t[p].cnt+1,1)%MOD;
            t[p].cnt++;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(fl<=mid) modify(ls,fl,fr);
        if(fr>mid) modify(rs,fl,fr);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].sum;
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(fl<=mid) ret=query(ls,fl,fr);
        if(fr>mid) ret=(ret+query(rs,fl,fr))%MOD;
        return ret;
    }
    #undef ls
    #undef rs
}sg;

int getphi(int x){
    int res=x;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            res=res/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) res=res/x*(x-1);
    return res;
}

void prework(){
    phi[ptot=1]=MOD;
    while(phi[ptot]>1){
        phi[ptot+1]=getphi(phi[ptot]);
        ptot++;
    }
    for(int i=1;i<=ptot;i++){
        pw1[i][0]=1;
        for(int j=1;j<=MB;j++) pw1[i][j]=pw1[i][j-1]*C%phi[i];
        int pww=pw1[i][MB];
        pw2[i][0]=1;
        for(int j=1;j*MB<=2*MOD;j++) pw2[i][j]=pw2[i][j-1]*pww%phi[i];
    }
    c[0]=1;
    int z=0;
    while(c[z]<MOD&&z<=30){
        z++;
        c[z]=c[z-1]*C;
    }
    z--;
    for(int i=1;i<=n;i++){
        lim[i]=0;
        pw[0][i]=a[i];
        while(lim[i]<=z&&pw[lim[i]][i]<=z){
            pw[lim[i]+1][i]=pw1[1][pw[lim[i]][i]];
            lim[i]++;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>q>>MOD>>C;
    for(int i=1;i<=n;i++) cin>>a[i];
    prework();
    sg.build(1,1,n);
    while(q--){
        int op,l,r; cin>>op>>l>>r;
        if(op) cout<<sg.query(1,l,r)<<"\n";
        else sg.modify(1,l,r);
    }
    return 0;
}
