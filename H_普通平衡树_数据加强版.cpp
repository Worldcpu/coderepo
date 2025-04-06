#include<iostream>
using namespace std;
int n,op,x;
const int MN=1e7;
struct fhq{
    int l,r,size,val,dat;
}t[MN+15];
int root=0,tot=0;
int newnode(int k){
    t[++tot].val=k;
    t[tot].dat=rand();
    t[tot].size=1;
    return tot;
}
void pushup(int p){
    t[p].size=t[t[p].l].size+t[t[p].r].size+1;
}
void split(int p,int k,int &x,int &y){
    if(!p){
        x=y=0;
        return;
    }
    if(t[p].val<=k){
        x=p;
        split(t[p].r,k,t[p].r,y);
    }else{
        y=p;
        split(t[p].l,k,x,t[p].l);
    }
    pushup(p);
}
int merge(int x,int y){
    if(!x||!y) return x+y;
    if(t[x].dat<t[y].dat){
        t[x].r=merge(t[x].r,y);
        pushup(x);
        return x;
    }else{
        t[y].l=merge(x,t[y].l);
        pushup(y);
        return y;
    }
}
void insert(int k){
    int x,y;
    split(root,k,x,y);
    int z=newnode(k);
    root=merge(merge(x,z),y);
}
void del(int k){
    int x,y,z;
    split(root,k,x,z);
    split(x,k-1,x,y);
    y=merge(t[y].l,t[y].r);
    root=merge(merge(x,y),z);
}
int getrank(int k){
    int x,y;
    split(root,k-1,x,y);
    int ans=t[x].size+1;
    root=merge(x,y);
    return ans;
}
int topk(int p,int k){
    int lz=t[t[p].l].size;
    if(lz+1==k) return t[p].val;
    if(lz>=k) return topk(t[p].l,k);
    else return topk(t[p].r,k-lz-1);
}
int getpre(int k){
    int x,y;
    split(root,k-1,x,y);
    int ans=topk(x,t[x].size);
    root=merge(x,y);
    return ans;
}
int getback(int k){
    int x,y;
    split(root,k,x,y);
    int ans=topk(y,1);
    root=merge(x,y);
    return ans;
}
int main(){
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int p;
        cin>>p;
        insert(p);
    }
    int last=0,ans=0;
    while (m--)
    {
        cin>>op>>x;
        x^=last;
        if(op==1) insert(x);
        if(op==2) del(x);
        if(op==3) last=getrank(x),ans^=last;
        if(op==4) last=topk(root,x),ans^=last;
        if(op==5) last=getpre(x),ans^=last;
        if(op==6){
            last=getback(x),ans^=last;
        }
    }
    cout<<ans;
    return 0;
}