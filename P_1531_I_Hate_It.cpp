#include<iostream>
using namespace std;
const int MN=2e5+15;
int n,m;
int a[MN];
struct segtree
{
    int l,r,val;
}t[4*MN];
void pushup(int p){
    t[p].val=max(t[p*2].val,t[p*2+1].val);
}
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].val=a[l];
        return;
    }
    int mid=l+r>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    pushup(p);
}
void change(int p,int f,int b){
    if(t[p].l==t[p].r){
        if(t[p].val<b){
            t[p].val=b;
        }
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=f){
        change(p*2,f,b);
    }
    if(mid<f){
        change(p*2+1,f,b);
    }
    pushup(p);
}
int ask(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].val;
    }
    int ret=-114514,mid=t[p].l+t[p].r>>1;
    if(mid>=fl){
        ret=max(ret,ask(p*2,fl,fr));
    }
    if(mid<fr){
        ret=max(ret,ask(p*2+1,fl,fr));
    }
    return ret;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    while (m--)
    {
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='Q'){
            cout<<ask(1,x,y)<<endl;
        }else change(1,x,y);
    }
    
    return 0;
}