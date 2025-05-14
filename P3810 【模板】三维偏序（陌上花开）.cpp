#include<bits/stdc++.h>
using namespace std;
const int MN=2e5+15;
struct node
{
    int x,y,z,ans,cnt;
}a[MN],b[MN];

// cnt[k]表示偏序对数量恰好为k的点数
int n,cnt[MN],t[MN];
int mk,nn;
bool cmp1(node u,node v){
    if(u.x==v.x){
        if(u.y==v.y){
            return u.z<v.z;
        }
        return u.y<v.y;
    }
    return u.x<v.x;
}
bool cmp2(node u,node v){
    if(u.y==v.y){
        return u.z<v.z;
    }
    return u.y<v.y;
}
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

void cdq(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    sort(a+l,a+mid+1,cmp2);
    sort(a+mid+1,a+r+1,cmp2);
    int i=mid+1,j=l;
    while (i<=r)
    {
        while (a[j].y<=a[i].y&&j<=mid)
        {
            add(a[j].z,a[j].cnt);
            j++;
        }
        a[i].ans+=query(a[i].z);
        i++;
    }
    for(i=l;i<j;i++){
        add(a[i].z,-a[i].cnt);
    }
}

int main(){
    cin>>nn>>mk;
    for(int i=1;i<=nn;i++){
        cin>>b[i].x>>b[i].y>>b[i].z;
    }
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
    cdq(1,n);
    for(int i=1;i<=n;i++){
        cnt[a[i].ans+a[i].cnt-1]+=a[i].cnt;
    }
    for(int i=0;i<nn;i++){
        cout<<cnt[i]<<'\n';
    }
    return 0;
}
