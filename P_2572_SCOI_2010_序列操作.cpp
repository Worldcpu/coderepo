#include<bits/stdc++.h>
#define il inline
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;
int n,m;
struct segtree{
    int l,r;
    bool isrev;
    int iscov=-1;
    int mxcon[2],sum1,ml[2],mr[2];
}t[MN<<2];
il void pushup(int p){
    t[p].sum1=t[ls].sum1+t[rs].sum1;

    t[p].ml[0]=t[ls].ml[0];
    t[p].mr[0]=t[rs].mr[0];
    t[p].ml[1]=t[ls].ml[1];
    t[p].mr[1]=t[rs].mr[1];

    if(t[ls].ml[0]==(t[ls].r-t[ls].l+1)){
        t[p].ml[0]=(t[ls].r-t[ls].l+1)+t[rs].ml[0];
    }else if(t[ls].ml[1]==(t[ls].r-t[ls].l+1)){
        t[p].ml[1]=(t[ls].r-t[ls].l+1)+t[rs].ml[1];
    }
    if(t[rs].mr[0]==(t[rs].r-t[rs].l+1)){
        t[p].mr[0]=(t[rs].r-t[rs].l+1)+t[ls].mr[0];
    }else if(t[rs].mr[1]==(t[rs].r-t[rs].l+1)){
        t[p].mr[1]=(t[rs].r-t[rs].l+1)+t[ls].mr[1];
    }

    t[p].mxcon[0]=max({t[ls].mxcon[0],t[rs].mxcon[0],t[ls].mr[0]+t[rs].ml[0]});
    t[p].mxcon[1]=max({t[ls].mxcon[1],t[rs].mxcon[1],t[ls].mr[1]+t[rs].ml[1]});
}

void pushdown(int p){
    if(t[p].iscov!=-1){
        t[ls].mxcon[0]=t[ls].ml[0]=t[ls].mr[0]=(t[ls].r-t[ls].l+1)*(!t[p].iscov);
        t[rs].mxcon[0]=t[rs].ml[0]=t[rs].mr[0]=(t[rs].r-t[rs].l+1)*(!t[p].iscov);

        t[ls].sum1=t[ls].mxcon[1]=t[ls].ml[1]=t[ls].mr[1]=(t[ls].r-t[ls].l+1)*(t[p].iscov);
        t[rs].sum1=t[rs].mxcon[1]=t[rs].ml[1]=t[rs].mr[1]=(t[rs].r-t[rs].l+1)*(t[p].iscov);

        t[ls].isrev=t[rs].isrev=0;
        t[ls].iscov=t[rs].iscov=t[p].iscov;
        t[p].iscov=-1;
    }
    if(t[p].isrev){
        swap(t[ls].mxcon[0],t[ls].mxcon[1]);
        swap(t[rs].mxcon[0],t[rs].mxcon[1]);

        swap(t[ls].ml[0],t[ls].ml[1]);
        swap(t[rs].ml[0],t[rs].ml[1]);

        swap(t[ls].mr[0],t[ls].mr[1]);
        swap(t[rs].mr[0],t[rs].mr[1]);

        t[ls].sum1=(t[ls].r-t[ls].l+1)-t[ls].sum1;
        t[rs].sum1=(t[rs].r-t[rs].l+1)-t[rs].sum1;

        t[ls].isrev^=1;
        t[rs].isrev^=1;
        t[p].isrev=0;
    }
}
int a[MN];
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    t[p].iscov=-1;
    if(l==r){
        t[p].sum1=t[p].mxcon[1]=t[p].ml[1]=t[p].mr[1]=a[l];
        t[p].mxcon[0]=t[p].ml[0]=t[p].mr[0]=!(a[l]);
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

void cover(int p,int fl,int fr,int k){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].iscov=k;
        t[p].mxcon[0]=t[p].ml[0]=t[p].mr[0]=(t[p].r-t[p].l+1)*(!k);
        t[p].sum1=t[p].mxcon[1]=t[p].ml[1]=t[p].mr[1]=(t[p].r-t[p].l+1)*k;
        t[p].isrev=0;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) cover(ls,fl,fr,k);
    if(mid<fr) cover(rs,fl,fr,k);
    pushup(p);
}

void doreverse(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].isrev^=1;
        swap(t[p].ml[0],t[p].ml[1]);
        swap(t[p].mr[0],t[p].mr[1]);
        swap(t[p].mxcon[0],t[p].mxcon[1]);
        t[p].sum1=(t[p].r-t[p].l+1)-t[p].sum1;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl){
        doreverse(ls,fl,fr);
    }
    if(mid<fr){
        doreverse(rs,fl,fr);
    }
    pushup(p);
}

int querysum(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].sum1;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1,ret=0;
    if(mid>=fl) ret+=querysum(ls,fl,fr);
    if(mid<fr) ret+=querysum(rs,fl,fr);
    return ret;
}

segtree querymxc(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p];
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fr){
        return querymxc(ls,fl,fr);
    }
    else if(mid<fl){
        return querymxc(rs,fl,fr);
    }else{
        segtree ln=querymxc(ls,fl,fr),rn=querymxc(rs,fl,fr);
        segtree ret;

        ret.ml[0]=ln.ml[0];
        ret.mr[0]=rn.mr[0];
        ret.ml[1]=ln.ml[1];
        ret.mr[1]=rn.mr[1];

        if(ln.ml[0]==(ln.r-ln.l+1)){
            ret.ml[0]=(ln.r-ln.l+1)+rn.ml[0];
        }else if(ln.ml[1]==(ln.r-ln.l+1)){
            ret.ml[1]=(ln.r-ln.l+1)+rn.ml[1];
        }

        if(rn.mr[0]==(rn.r-rn.l+1)){
            ret.mr[0]=(rn.r-rn.l+1)+ln.mr[0];
        }else if(rn.mr[1]==(rn.r-rn.l+1)){
            ret.mr[1]=(rn.r-rn.l+1)+ln.mr[1];
        }

        ret.mxcon[0]=max({ln.mxcon[0],rn.mxcon[0],ln.mr[0]+rn.ml[0]});
        ret.mxcon[1]=max({ln.mxcon[1],rn.mxcon[1],ln.mr[1]+rn.ml[1]});
        return ret;
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int op,x,y;
    build(1,1,n);
    while (m--)
    {
        cin>>op>>x>>y;
        x++;
        y++;
        if(op==0){
            cover(1,x,y,0);
        }
        if(op==1){
            cover(1,x,y,1);
        }
        if(op==2){
            doreverse(1,x,y);
        }
        if(op==3){
            cout<<querysum(1,x,y)<<'\n';
        }
        if(op==4){
            cout<<querymxc(1,x,y).mxcon[1]<<'\n';
        }
    }
    
    return 0;
}