#include<iostream>
#define ls t[p].l
#define rs t[p].r
using namespace std;
const int MN=1e5+15;
struct fhqtree
{
    int l,r,val,size,dat;
    bool revtag;
}t[MN];
int n,m,root,tot;
int newnode(int k){
    t[++tot].val=k;
    t[tot].dat=rand();
    t[tot].size=1;
    return tot;
}
void doreverse(int p){
    if(t[p].revtag){
        swap(ls,rs);
        t[ls].revtag^=1;
        t[rs].revtag^=1;
        t[p].revtag=0;
    }
}
void pushdown(int p){
    doreverse(p);
    if(ls) doreverse(ls);
    if(rs) doreverse(rs);
}
void pushup(int p){
    t[p].size=t[ls].size+t[rs].size+1;
}
void split(int p,int k,int &x,int &y){
    if(!p){
        x=y=0;
        return;
    }
    pushdown(p);
    if(k>t[ls].size){
        x=p;
        k-=t[ls].size+1;
        split(rs,k,rs,y);
    }else{
        y=p;
        split(ls,k,x,ls);
    }
    pushup(p);
}
int merge(int x,int y){
    if(!x||!y){
        return x+y;
    }
    if(t[x].dat<t[y].dat){
        pushdown(x);
        t[x].r=merge(t[x].r,y);
        pushup(x);
        return x;
    }else{
        pushdown(y);
        t[y].l=merge(x,t[y].l);
        pushup(y);
        return y;
    }
}
void pushback(int k){
    root=merge(root,newnode(k));
}
void reverse(int fl,int fr){
    int x,y,z;
    split(root,fr,x,z);
    split(x,fl-1,x,y);
    t[y].revtag^=1;
    doreverse(y);
    root=merge(merge(x,y),z);
}
void output(int p){
    if(!p) return;
    pushdown(p);
    output(t[p].l);
    cout<<t[p].val<<" ";
    output(t[p].r);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        pushback(i);
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        reverse(l,r);
    }
    output(root);
    return 0;
}