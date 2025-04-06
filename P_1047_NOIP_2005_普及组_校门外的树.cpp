#include<iostream>
#define ls t[p].l
#define rs t[p].r
using namespace std;
const int MN=1e4+15;
int l,m;
struct segtreee
{
    int l,r,val;
    int rm;
}t[4*MN];
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].val=1;
        return;
    }
    int mid=l+r>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    t[p].val=t[p*2].val+t[p*2+1].val;
}
void pushdown(int p){
    if(t[p].rm){
        t[p*2].rm=t[p*2+1].rm=1;
        t[p*2].val=t[p*2+1].val=0;
        t[p].rm=0;
    }
}
void change(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].rm=1;
        t[p].val=0;
        return;
    }
    pushdown(p);
    int mid=ls+rs>>1;
    if(mid>=fl){
        change(p*2,fl,fr);
    }
    if(mid<fr){
        change(p*2+1,fl,fr);
    }
    t[p].val=t[p*2].val+t[p*2+1].val;
}
int main(){
    cin>>l>>m;
    ++l;
    build(1,1,l);
    //cout<<t[1].l<<" "<<t[1].r<<endl<<t[1].val<<endl;
    while (m--)
    {
        int u,v;
        cin>>u>>v;
        ++u;
        ++v;
        change(1,u,v);
    }
    pushdown(1);
    cout<<t[1].val;
    return 0;
}