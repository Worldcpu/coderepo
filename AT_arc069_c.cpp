#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int a[MN],n,ans[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int mx,mxpos;

        Node(int mxx=-INF,int mxp=0){
            mx=mxx,mxpos=mxp;
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.mx=max(x.mx,y.mx);
            if(ret.mx==x.mx){
                ret.mxpos=x.mxpos;
            }else ret.mxpos=y.mxpos;
            return ret;
        }
    };

    struct SNode{
        int l,r;
        Node val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=Node(a[l],l);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int pos){
        if(t[p].l==t[p].r){
            t[p].val=Node(0,t[p].l);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) update(ls,pos);
        else update(rs,pos);
        pushup(p);
    }


}sg;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sg.build(1,1,n);
    auto qwq=sg.t[1].val;
    int nowp=qwq.mxpos,nowv=qwq.mx,dtot=1;
    sg.update(1,nowp);
    while(nowp!=1){
        int nxtp=sg.t[1].val.mxpos;
        ans[nowp]+=(nowv-sg.t[1].val.mx)*dtot;
        dtot++;
        nowv=sg.t[1].val.mx;
        sg.update(1,nxtp);
        if(nxtp<nowp) nowp=nxtp;
    }
    for(int i=1;i<=n;i++){
        if(a[i]<=a[1]){
            ans[1]+=a[i];
        }else ans[1]+=a[1];
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}