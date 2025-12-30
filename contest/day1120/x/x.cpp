#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,V=1e5+1;
int rt[MN],n,a[MN],q;
int l1,r1,l2,r2;

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson,val;
    }t[MN*50];
    int tot;

    void init(){
        for(int i=0;i<=tot;i++) memset(&t[i],0,sizeof(t[i]));
        tot=0;
    }

    void modify(int &p,int lst,int l,int r,int pos){
        p=++tot;
        t[p]=t[lst];
        t[p].val++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,t[lst].lson,l,mid,pos);
        else modify(rs,t[lst].rson,mid+1,r,pos);
    }

    // return rt[x]-rt[y]
    int query(int x,int y,int l,int r,int fl,int fr){
        if(l>=fl&&r<=fr){
            return t[x].val-t[y].val;
        }
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) ret+=query(t[x].lson,t[y].lson,l,mid,fl,fr);
        if(mid<fr) ret+=query(t[x].rson,t[y].rson,mid+1,r,fl,fr);
        return ret;
    }
}sg;

void init(){
    sg.init();
    sg.modify(rt[1],0,0,V*2,V);
}

int solve(int pos){
    init();
    int cnt=0,res=0;
    for(int i=1;i<=n;i++){
        if(a[i]>pos) cnt--;
        else cnt++;
        sg.modify(rt[i+1],rt[i],0,V*2,cnt+V);
        res+=sg.query(rt[(i-l2+1<0?0:i-l2+1)],rt[(i-r2<0?0:i-r2)],0,V*2,0,cnt+V);
    }   
    return (res);
}

signed main(){
    freopen("x.in","r",stdin);
    freopen("x.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cin>>q;
    while(q--){
        cin>>l1>>r1>>l2>>r2;
        cout<<(solve(r1)-solve(l1-1))<<'\n';
    }
    return 0;
}

// noi plus
// 30分可以主席树 nlogn 预处理 logn 求中位数
// 特殊性质 A 不就是正解？给了 hyw？
// 弱化一下问题，发现如果给你一个中位数为 [1,k] 的范围你会做，维护一个前缀cnt，查询有多少数 <= 当前 cnt 即可。
// 然后怎么解决区间范围问题？离线扫描线？再差分一次扫描线或者主席树维护。不过两个做法主席树都要写。

// 0也要算？？？？？？
// wcnm调不出来，已经1个小时18分钟了。