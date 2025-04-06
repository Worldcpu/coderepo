#include<iostream>
#define ll long long
#define ls t[p].l
#define rs t[p].r
#define endl '\n'
using namespace std;
const int MN=1e5+15;
struct fhqtree
{
    int l,r,size,dat;
    ll val;
}t[MN];
int tt=0,root=0;
int newnode(int k){
    t[++tt].val=k;
    t[tt].dat=rand();
    t[tt].l=t[tt].r=0;
    t[tt].size=1;
    return tt;
}
void pushup(int p){
    t[p].size=t[ls].size+t[rs].size+1;
}
void split(int p,int k,int &x,int &y){
    if(!p){
        x=y=0;
        return;
    }
    if(t[p].val<=k){
        x=p;
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
    int x,y,z;
    split(root,k,x,y);
    z=newnode(k);
    root=merge(merge(x,z),y);
}
void del(int k){
    int x,y,z;
    split(root,k,x,y);
    split(x,k-1,x,z);
    z=merge(t[z].l,t[z].r);
    root=merge(merge(x,z),y);
}
int getrankval(int v){
    int x,y,z;
    split(root,v-1,x,y);
    int ans=t[x].size+1;
    root=merge(x,y);
    return ans;
}
int topk(int p,int k){
    int lz=t[ls].size;
    if(lz+1==k){
        return t[p].val;
    }
    if(lz>=k) return topk(ls,k);
    return topk(rs,k-t[ls].size-1);
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
    
    int n,m=0,op,ans=0;
    int x;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int p;
        cin>>p;
        insert(p);
    }
    int la;
    while (m--)
    {
        cin>>op>>x;
        x^=la;
        if(op==1) insert(x);
        if(op==2) del(x);
        if(op==3){ la=getrankval(x);ans^=la;}
        if(op==4) {la=topk(root,x);ans^=la;}
        if(op==5) {la=getpre(x);ans^=la;}
        if(op==6){
            la=getback(x);
            ans^=la;
        }
    }
    cout<<ans;
    return 0;
}