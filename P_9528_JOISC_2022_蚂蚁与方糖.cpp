#include <algorithm>
#include<bits/stdc++.h>
#include <ctime>
#define int long long
using namespace std;
constexpr int MN=1e5+15,INF=1e9;
struct Query{
    int t,x,a;
}qry[MN];
int q,L,lsan[MN],tot;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,val,add;
        int f[2][2];
    }t[MN<<2];

    void pushup(int p){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                t[p].f[i][j]=-INF;
            }
        }
        for(int x1=0;x1<2;x1++){
            for(int y1=0;y1<2;y1++){
                for(int x2=0;x2<2;x2++){
                    for(int y2=0;y2<2;y2++){
                        t[p].f[x1][y1]=max(t[p].f[x1][y2],t[ls].f[x1][y1]+t[rs].f[x2][y2]+(x2&y1)*t[p].val);
                    }
                }
            }
        }
    }

    void doadd(int p,int k){
        t[p].add+=k;
        t[p].val+=k;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                t[p].f[i][j]-=k;
            }
        }
        t[p].f[0][0]=max(t[p].f[0][0],0ll);
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l,t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modifyf(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].f[1][1]+=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modifyf(ls,pos,k);
        else modifyf(rs,pos,k);
        pushup(p);
    }

    void modifyg(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modifyg(ls,fl,fr,k);
        if(mid<fr) modifyg(rs,fl,fr,k);
        if(mid>=fl&&mid<fr) t[p].val+=k;
        pushup(p); 
    }

    int query(){
        int ret=-INF;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                ret=max(ret,t[1].f[i][j]);
            }
        }
        return ret;
    }

#undef ls
#undef rs
}sg;


signed main(){
    cin>>q>>L;
    tot=1;
    for(int i=1;i<=q;i++){
        cin>>qry[i].t>>qry[i].x>>qry[i].a;
        if(qry[i].t==1){
            lsan[++tot]=qry[i].x;
        }
    }
    sort(lsan+1,lsan+1+tot);
    tot=unique(lsan+1,lsan+1+tot)-lsan-1;
    sg.build(1,1,tot);
    int ans=0;
    for(int i=1;i<=q;i++){
        if(qry[i].t==1){
            ans+=qry[i].a;
            int pos=lower_bound(lsan+1, lsan+1+tot, qry[i].x)-lsan;
            sg.modifyf(1,pos,qry[i].a);
        }else{
            int posl=lower_bound(lsan+1,lsan+1+tot,qry[i].x-L)-lsan,posr=upper_bound(lsan+1,lsan+1+tot,qry[i].x+L)-lsan-1;
            sg.modifyg(1,posl,posr,qry[i].a);
        }
        cout<<ans-sg.query()<<'\n';
    }
    return 0;
}