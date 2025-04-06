#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int MN=5e5,MNI=4*1e6;
//这里是区间操作，不维护有序，有序请右转FHQtreap
struct fhq{
    int l,r,size,dat,val;
    //懒惰标记
    bool revtag,covtag;
    int covval;//区间覆盖标记与权值，翻转标记
    int sum,mpre,mback,msum;//区间和，最大前缀和，最大后缀和，最大区间和
//  其中有一个细节点是，mpre 和 msuf 要时刻保证至少为 0，因为我们只考虑计算非负的求和成分。
}t[MN+15];

int n,m;

//时刻注意！！！
//父节点代表的区间=左孩子代表区间+右孩子代表区间+父节点


int tot=0,root=0;
//垃圾回收,用栈实现
//不是为啥要回收？因为内存不够啊
//先利用删除的节点，这样就不用炸内存啦
int gcstack[MN];
int gctop=0;
void gc(int p){
    if(!p) return;
    gcstack[gctop++]=p;
    //先用叶子再用根，根回收完就回收左右子树
    gc(t[p].l);
    gc(t[p].r);
}
int newnode(int k){
    int i = gctop ? gcstack[--gctop] : ++tot;
    // if(gctop){//有垃圾！
    //     i=gcstack[--gctop];//我吃
    // }else i=++tot;//没有就拿

    //普通的新建节点
    memset(&t[i],0,sizeof(t[i]));
    t[i].dat=rand();
    t[i].size=1;
    t[i].msum=t[i].sum=t[i].val=k;
    t[i].mpre=t[i].mback=max(0,k);
    return i;
}
void pushup(int p){
    t[p].size=t[t[p].l].size+t[t[p].r].size+1;
    t[p].sum=t[t[p].l].sum+t[t[p].r].sum+t[p].val;
    //t[p].mpre=max({t[t[p].l].sum,t[t[p].l].sum+t[p].val+t[t[p].r].mpre,0});
    t[p].mback=max({t[t[p].r].mback,t[t[p].l].mback+t[p].val+t[t[p].r].sum,0});
    t[p].mpre = max({t[t[p].l].mpre, t[t[p].l].sum + t[p].val + t[t[p].r].mpre, 0});
    t[p].msum=max(t[p].val,t[t[p].l].mback+t[t[p].r].mpre+t[p].val);
    if(t[p].l){
        t[p].msum=max(t[p].msum,t[t[p].l].msum);
    }
    if(t[p].r){
        t[p].msum=max(t[p].msum,t[t[p].r].msum);
    }
}
inline void cover(int p){
    if(!t[p].covtag) return;
    int c=t[p].val=t[p].covval;
    // 因为采用延迟更新, 所以子树的和不再等于: 左右子树的和+p.val
    // 这里要同步修改掉区间和 sum 和依赖它的 mpre, msuf 和 msum

    int s=t[p].sum=c*t[p].size;//加法结合为乘
    t[p].mpre=t[p].mback=max(0,s);
    t[p].msum=max(c,s);//是单独选自己还是整个区间和

    //下传标记，和线段树差不多
    t[t[p].l].covtag=t[t[p].r].covtag=1;
    t[t[p].l].covval=t[t[p].r].covval=c;
    t[p].covtag=t[p].covval=0;
}
void reverse(int p){
    if(!t[p].revtag) return;
    swap(t[p].l,t[p].r);
    swap(t[p].mpre,t[p].mback);
    t[t[p].l].revtag^=1;//自行想为啥用异或
    t[t[p].r].revtag^=1;
    t[p].revtag=0;
}
inline void pushdown(int p){
    if(!p) return;
    cover(p);//覆盖下传
    reverse(p);//翻转下传
//如果仅仅对一个节点做了延迟标记，而没有做更新，那么 pushup 维护区间和的过程会算错。

//比方说，对节点 p 打了延迟更新的标记，它的父节点是 q，另一个孩子是 r，如果下一次 分裂 或者 合并 只路过了 r，而没有路过 p， 延迟更新就不会触发，pushup 函数对 q 节点的求和就会算错。

//简称：我分树的时候可能没分到另一个（也就是不会更新孩子节点）导致mpre mback msum全算错

//所以提前分
    if(t[p].l) cover(t[p].l),reverse(t[p].l);
    if(t[p].r) cover(t[p].r),reverse(t[p].r);
}
void split(int p,int k,int &x,int &y){//这里的k是数组下表，分成[1,k]和[k+1,n]两个区间子树
    if(!p){
        x=y=0;
        return;
    }
    pushdown(p);
    if(k>t[t[p].l].size){//由于维护的是下表，那么子树大小就是元素个数，
        x=p;
        k-=t[t[p].l].size+1;
        split(t[p].r,k,t[p].r,y);
    }else{
        y=p;
        split(t[p].l,k,x,t[p].l);
    }
    pushup(p);
}
int merge(int x,int y){//只是多了个pushdown，因为合并吗，不懂看线段树
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
//刨子树x，y，z。
//y是从第k个开始的tot个数字的区间子树
inline void qujian(int &x,int &y,int &z,int k,int tott){
    int l=k,r=k+tott-1;
    split(root,r,x,z);//x为[1,r] z为[r+1,N];
    split(x,l-1,x,y);//抛丸后x为[1,l-1],y为[l,r]
}
int toinsert[MNI];//插入序列

void pushback(int k){//字面意思的追加
    root=merge(root,newnode(k));
}

//批量插入 分治建树，复杂度O(mlogm+logn)
int build(int l,int r){
    if(l==r){
        return newnode(toinsert[l]);
    }
    int mid=(l+r)>>1;
    return merge(build(l,mid),build(mid+1,r));
}
void plinsert(int k,int tot){
    int x,y;
    split(root,k,x,y);
    int z=build(1,tot);
    root=merge(merge(x,z),y);
}
//批量删除 从第k个位置删tott个元素
void del(int k,int tott){
    int x,y,z;
    qujian(x,y,z,k,tott);
    //此时y就是[k,k+tot]这个下表区间的子树
    gc(y);
    root=merge(x,z);
    //合并x，z，刚好舍掉y树
}
//求最大值，还是要qujian让后直接返回y的sum
int getsum(int k,int tott){
    int x,y,z;
    qujian(x,y,z,k,tott);
    int ans=t[y].sum;
    merge(merge(x,y),z);
    return ans;
}
//最大子段和 有负数！
//当子段和路过p，最大子段和等于下面两种子情况之最大： 
//左孩子区间的最大后缀和 + p 的值 + 右孩子区间的最大前缀和。 
//或者只取 p 单个节点本身。

//当不路过p
//此时，容易知道 p.msum 来自左、右孩子的 msum 之最大者。
int maxsumroot(){//获取[1,N]最大区间和
    return t[root].msum;
}
//从k开始，t个元素覆盖为c
void docover(int k,int tott,int c){
    int x,y,z;
    qujian(x,y,z,k,tott);//经典化区间
    t[y].covtag=1;
    t[y].covval=c;
    cover(y);//先更新一下
    root=merge(merge(x,y),z);
}

//区间翻转
//区间翻转，可以逐层交换左右子树来逐步完成。
//也就是说，pushdown 下行过程中，只需要每次交换左右子树即可。
//交换左右子树会影响到 最大前缀和 mpre 和 最大后缀和 msuf 的含义，所以要一并维护。
//即要交换前后缀和见reverse函数
void doreverse(int k,int tott){
    int x,y,z;
    qujian(x,y,z,k,tott);
    t[y].revtag^=1;
    reverse(y);
    root=merge(merge(x,y),z);
}
int gett(int k){
    int x,y,z;
    split(root,k,x,z);
    split(x,k-1,x,y);
    int ans=t[y].val;
    root=merge(merge(x,y),z);
    return ans;
}
int getmaxsum(int k,int tott){
    int x,y,z;
    qujian(x,y,z,k,tott);
    int ans=t[y].msum;
    root=merge(merge(x,y),z);
    return ans;
}
void output(int p) {
    if (!p) return;
    pushdown(p);
    output(t[p].l);
    printf("%d ", t[p].val);
    output(t[p].r);
}
int main(){
    #ifndef ONLINE_JUDGE
    auto pp=freopen("a.in","r",stdin);
    #endif
    // if(pp==NULL){
    //     cout<<"NO"<<endl;
    //     return 0;
    // }
//以下代码见P2042
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        pushback(v);
    }
    string op;
    while (m--)
    {
        int k,c,tott;
        cin>>op;
        //cout<<"OP:"<<op<<endl;
        if(op[0]=='I'){
            cin>>k>>tott;
            for(int i=1;i<=tott;i++){
                cin>>toinsert[i];
            }
            plinsert(k,tott);
        }else if(op[0]=='D'){
            cin>>k>>tott;
            del(k,tott);
        }else if(op[0]=='R'){
            cin>>k>>tott;
            doreverse(k,tott);
        }else if(op[0]=='G'&&op[3]=='-'){
            cin>>k>>tott;
            cout<<getsum(k,tott)<<endl;
        }else if(op[0]=='G'){
            //cout<<"M:"<<m<<endl;
            cin>>k;
            cout<<gett(k)<<endl;
        }
        else if(op[0]=='M'){
            if(op[2]=='K'){
                cin>>k>>tott>>c;
                docover(k,tott,c);
            }else{
                cin>>k>>tott;
                cout<<getmaxsum(k,tott)<<endl;
            }
        }
        // cout<<"M="<<m<<endl;
        // output(root);
        // cout<<endl;
    }
    
    return 0;
}