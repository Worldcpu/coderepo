#include<iostream>
using namespace std;
int n,op,x,leave=0;
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
    split(root,k-1,x,z);
    leave+=t[x].size;
    root=z;
}
int getrank(int k){
    int x,y;
    split(root,k-1,x,y);
    int ans=t[x].size+1;
    root=merge(x,y);
    return ans;
}
int topk(int p,int k){
    int rz=t[t[p].r].size;
    if(rz+1==k) return t[p].val;
    if(rz>=k) return topk(t[p].r,k);
    else return topk(t[p].l,k-rz-1);
}
// int getpre(int k){
//     int x,y;
//     split(root,k-1,x,y);
//     int ans=topk(x,t[x].size);
//     root=merge(x,y);
//     return ans;
// }
// int getback(int k){
//     int x,y;
//     split(root,k,x,y);
//     int ans=topk(y,1);
//     root=merge(x,y);
//     return ans;
// }
int main(){
    int minn,ans=0,py=0,cnt=0;
    cin>>n>>minn;
    while (n--)
    {
        char op;
        int k;
        cin>>op>>k;
        if(op=='I'){
            if(k>=minn){
                insert(k-py);
            }
            // insert(k);
        }else if(op=='A'){
            py+=k;
        }else if(op=='S'){
            py-=k;
            del(minn-py);
        }else if(op=='F'){
            if(k>t[root].size){
                cout<<-1<<endl;
            }
            else cout<<topk(root,k)+py<<endl;
        }
    }
    cout<<leave;
    return 0;
}