#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Query{
    int op,x,y,t,id;
}q[MN];
int n,m,qtot,ans[MN],a[MN],pos[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

}bit;

bool cmp2(Query x,Query y){
    return x.x<y.x;
}

void cdq(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    int i=l,j=mid+1;
    sort(q+l,q+mid+1,cmp2); // 使用sort反而正确
    sort(q+mid+1,q+r+1,cmp2);
    while(j<=r){
        while(q[i].x<=q[j].x&&i<=mid){
            bit.update(q[i].y,q[i].op);
            i++;
        }
        ans[q[j].id]+=q[j].op*(bit.query(n)-bit.query(q[j].y));
        j++;
    }
    for(int p=l;p<i;p++){
        bit.update(q[p].y,-q[p].op);
    }
    i=r,j=mid;
    while(i>mid){
        while(j>=l&&q[j].x>=q[i].x) bit.update(q[j].y,q[j].op),j--;
        ans[q[i].id]+=q[i].op*bit.query(q[i].y-1);
        i--;
    }
    for(i=mid;i>j;i--) bit.update(q[i].y,-q[i].op);
    // inplace_merge(q+l+1,q+mid+1,q+r+1,cmp2); 错误
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]]=i;
        q[++qtot]={1,i,a[i],0,0};
    }
    for(int i=1;i<=m;i++){
        int x;
        cin>>x;
        q[++qtot]={-1,pos[x],x,i,i};
    }
    // sort(q+1,q+1+qtot,cmp1);
    cdq(1,qtot);
    for(int i=1;i<=m;i++) ans[i]+=ans[i-1];
    for(int i=0;i<m;i++) cout<<ans[i]<<'\n';
    return 0;
}