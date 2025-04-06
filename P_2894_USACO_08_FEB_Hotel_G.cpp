#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=5e4+15,NINF=-1e9;
int n,m;
struct segtree{
    int l,r;
    int ml,mr,msum;
    //lazy=1表示清空，2为入住
    int lazy;
}t[MN<<2];
void pushup(int p){
    // t[p].sum=t[ls].sum+t[rs].sum;
    t[p].ml=t[ls].ml;
    t[p].mr=t[rs].mr;
    if(t[ls].msum==(t[ls].r-t[ls].l+1)){
        t[p].ml=t[ls].msum+t[rs].ml;
    }
    if(t[rs].msum==(t[rs].r-t[rs].l+1)){
        t[p].mr=t[rs].msum+t[ls].mr;
    }
    t[p].msum=max({t[ls].msum,t[rs].msum,t[ls].mr+t[rs].ml});
}
void pushdown(int p){
    if(t[p].lazy==1){
        t[ls].ml=t[ls].mr=t[ls].msum=(t[ls].r-t[ls].l+1);
        t[rs].ml=t[rs].mr=t[rs].msum=(t[rs].r-t[rs].l+1);
        t[ls].lazy=t[rs].lazy=t[p].lazy;
        t[p].lazy=0;
    }
    if(t[p].lazy==2){
        t[ls].ml=t[ls].mr=t[ls].msum=t[rs].ml=t[rs].mr=t[rs].msum=0;
        t[ls].lazy=t[rs].lazy=t[p].lazy;
        t[p].lazy=0;
    }
}
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].ml=t[p].mr=t[p].msum=1;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
void clearroom(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].lazy=1;
        t[p].ml=t[p].mr=t[p].msum=(t[p].r-t[p].l+1);
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) clearroom(ls,fl,fr);
    if(mid<fr) clearroom(rs,fl,fr);
    pushup(p);
}
void updateroom(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].lazy=2;
        t[p].ml=t[p].mr=t[p].msum=0;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl)updateroom(ls,fl,fr);
    if(mid<fr) updateroom(rs,fl,fr);
    pushup(p);
}
int query(int p,int ms){
    if(t[p].l==t[p].r){
        return t[p].l;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(t[ls].msum>=ms){
        return query(ls,ms);
    }
    else if(t[ls].mr+t[rs].ml>=ms){
        return t[ls].r-t[ls].mr+1;
    }
    else return query(rs,ms);
}
int main(){
    cin>>n>>m;
    int op,x,y;
    build(1,1,n);
    while (m--)
    {
        cin>>op>>x;
        if(op==1){
            if(t[1].msum>=x){
                int left=query(1,x);
                cout<<left<<'\n';
                updateroom(1,left,left+x-1);
            }else cout<<0<<'\n';
        }else{
            cin>>y;
            clearroom(1,x,x+y-1);
        }
    }
    
    return 0;
}