#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int x[MN],y[MN],amx[MN],amn[MN],n,m;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mx[4],mn[4],tag;
    }t[MN<<2];

    void pushup(int p){
        for(int i=0;i<4;i++){
            t[p].mx[i]=max(t[ls].mx[i],t[rs].mx[i]);
            t[p].mn[i]=min(t[ls].mn[i],t[rs].mn[i]);
        }
    }

    void dotag(int p){
        int tmx=t[p].mx[0],tmn=t[p].mn[0];
        t[p].mx[0]=t[p].mx[1]; t[p].mn[0]=t[p].mn[1];
        t[p].mx[1]=t[p].mx[3]; t[p].mn[1]=t[p].mn[3];
        t[p].mx[3]=t[p].mx[2]; t[p].mn[3]=t[p].mn[2];
        t[p].mx[2]=tmx;        t[p].mn[2]=tmn;
        t[p].tag=(t[p].tag+1)%4;
    }

    void pushdown(int p){
        if(!t[p].tag) return;
        int k=t[p].tag;
        while(k--){
            dotag(ls);
            dotag(rs);
        }
        t[p].tag=0;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mn[0]=t[p].mx[0]=x[l]+y[l];
            t[p].mn[1]=t[p].mx[1]=x[l]-y[l];
            t[p].mn[2]=t[p].mx[2]=-x[l]+y[l];
            t[p].mn[3]=t[p].mx[3]=-x[l]-y[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            dotag(p);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr);
        if(mid<fr) modify(rs,fl,fr);
        pushup(p);
    }

    void query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            for(int i=0;i<4;i++){
                amx[i]=max(amx[i],t[p].mx[i]);
                amn[i]=min(amn[i],t[p].mn[i]);
            }
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) query(ls,fl,fr);
        if(mid<fr) query(rs,fl,fr);
        pushup(p);
    }

}sg;

void initans(){
    for(int i=0;i<4;i++){
        amx[i]=-INF;
        amn[i]=INF;
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    sg.build(1,1,n);
    while(m--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1){
            sg.modify(1,l,r);
        }else{
            initans();
            sg.query(1,l,r);
            int ans=0;
            for(int i=0;i<4;i++){
                ans=max(ans,amx[i]-amn[i]);
            }
            cout<<ans<<'\n';
        }
    }

    return 0;
}