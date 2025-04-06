#include<iostream>
#define endl '\n'
using namespace std;
const int MN=1e6+16;
struct hjttree
{
    int l,r,val;
}t[MN*42];//牢学长Renamoe曾言：“你就往内存限制开就行了！”

//开得节点数，原数组，各个版本的根，后面的意义自明
int tot,a[MN],root[MN],n,m;

//将t[k]的节点内容复制到新节点
int newnode(int k){
    t[++tot]=t[k];
    return tot;
}
int build(int p,int l,int r){
    p=++tot;//这里因为是动态开点所以就直接++tot了
    if(l==r){
        t[p].val=a[l];
        return tot;
    }
    int mid=l+r>>1;
    t[p].l=build(t[p].l,l,mid);
    t[p].r=build(t[p].r,mid+1,r);
    return p;
}

int update(int p,int l,int r,int loc,int k){
    p=newnode(p);//更新要新建节点
    if(l==r){
        t[p].val=k;
        //return p;
    }
    else{    
        int mid=l+r>>1;
        if(loc<=mid){
            t[p].l=update(t[p].l,l,mid,loc,k);
        }else{
            t[p].r=update(t[p].r,mid+1,r,loc,k);
        }
    }
    return p;
}
int query(int p,int l,int r,int x){
    if(l==r){
        return t[p].val;
    }
    int mid=l+r>>1;
    if(x<=mid){
        return query(t[p].l,l,mid,x);
    }else return query(t[p].r,mid+1,r,x);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    root[0]=build(0,1,n);//0表示最初的版本
    for(int i=1;i<=m;i++){
        int v,op,x,y;//v->访问版本
        cin>>v>>op>>x;
        if(op==1){
            cin>>y;
            root[i]=update(root[v],1,n,x,y);
        }else{
            cout<<query(root[v],1,n,x)<<endl;
            root[i]=root[v];//题目说了第二操作也要新建版本
        }
    }
    
    return 0;
}