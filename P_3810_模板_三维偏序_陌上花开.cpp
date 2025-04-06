#include<bits/stdc++.h>
using namespace std;
const int MN=2e5+15;
struct node
{
    int x,y,z,ans,cnt;
    // ans即偏序对点数，cnt即重复节点数
}a[MN],b[MN];

// cnt[k]表示偏序对数量恰好为k的点数
int n,cnt[MN],t[MN];
int mk,nn;

// cmp1用于初次排序以及去重
bool cmp1(node u,node v){
    if(u.x==v.x){
        if(u.y==v.y){
            return u.z<v.z;
        }
        return u.y<v.y;
    }
    return u.x<v.x;
}

//cmp2用于分治时合并保证升序
bool cmp2(node u,node v){
    if(u.y==v.y){
        return u.z<v.z;
    }
    return u.y<v.y;
}

// 树状数组
int lowbit(int x){
    return x&-x;
}
void add(int x,int k){
    while (x<=mk)
    {
       t[x]+=k;
       x+=lowbit(x);
    }
}

int query(int x){
    int ret=0;
    while (x)
    {
        ret+=t[x];
        x-=lowbit(x);
    }
    return ret;
}

// CDQWQ分治
void cdq(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    // 左右区间分治
    cdq(l,mid);
    cdq(mid+1,r);

    //保证合并是升序
    sort(a+l,a+mid+1,cmp2);
    sort(a+mid+1,a+r+1,cmp2);

    //i表示右区间指针，j即左区间指针
    int i=mid+1,j=l;
    while (i<=r)
    {
        //就是树状数组二维偏序
        while (a[j].y<=a[i].y&&j<=mid)
        {
            add(a[j].z,a[j].cnt);
            j++;
        }
        a[i].ans+=query(a[i].z);
        i++;
    }

    //记得清空树状数组不然下一次统计答案可能会冲突
    for(i=l;i<j;i++){
        add(a[i].z,-a[i].cnt);
    }
}

int main(){
    cin>>nn>>mk;
    for(int i=1;i<=nn;i++){
        cin>>b[i].x>>b[i].y>>b[i].z;
    }

    //去重PART
    sort(b+1,b+1+nn,cmp1);
    int c=0;
    for(int i=1;i<=nn;i++){
        c++;
        if(b[i].x!=b[i+1].x||b[i].y!=b[i+1].y||b[i].z!=b[i+1].z){
            a[++n]=b[i];
            a[n].cnt=c;
            c=0;
        }
    }
    //分治
    cdq(1,n);
    for(int i=1;i<=n;i++){
        cnt[a[i].ans+a[i].cnt-1]+=a[i].cnt;
        //cnt[k]表示偏序对数量恰好为k的点数
        //为什么是a[i].ans+a[i].cnt-1
        //因为重复的点之间也会相互形成逆序对
        //a[i].ans即其他点对i的贡献
        //a[i].w-1表示i自身重复的贡献，数量为w-1
    }
    for(int i=0;i<nn;i++){
        cout<<cnt[i]<<'\n';
    }
    return 0;
}