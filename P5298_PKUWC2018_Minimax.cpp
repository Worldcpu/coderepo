#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15,MOD=998244353,INV=796898467;
int ch[MN][2],b[MN],rt[MN],ans,n,val[MN],d[MN],dtot;

struct Segment{
#define ls t[p].lson
#define rs t[p].rson
    struct Node{
        int lson,rson,val,tag;
    }t[MN<<3];
    int tot;

    void dotag(int p,int k){
        t[p].val=t[p].val*k%MOD;
        t[p].tag=t[p].tag*k%MOD;
        return;
    }

    void pushdown(int p){
        if(!p) return;
        if(t[p].tag!=1){
            dotag(ls,t[p].tag);
            dotag(rs,t[p].tag);
            t[p].tag=1;
        }
    }

    void insert(int &p,int l,int r,int pos){
        if(!p){
            p=++tot;
            t[p].tag=1;
        }
        (t[p].val+=1)%=MOD;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) insert(ls,l,mid,pos);
        else insert(rs,mid+1,r,pos);
    }

    int merge(int x,int y,int lx,int rx,int ly,int ry,int k){
        if(!x&&!y) return 0;
        pushdown(x);
        pushdown(y);
        if(x&&!y){
            int p=++tot;
            t[p]=t[x];
            dotag(p,(ly*k%MOD+ry*((1-k+MOD)%MOD)%MOD)%MOD);
            return p;
        }
        if(!x&&y){
            int p=++tot;
            t[p]=t[y];
            dotag(p,(lx*k%MOD+rx*(1-k+MOD)%MOD)%MOD);
            return p;
        }
        int p=++tot;
        t[p].tag=1;
        ls=merge(t[x].lson,t[y].lson,lx,(rx+t[t[x].rson].val)%MOD,ly,(ry+t[t[y].rson].val)%MOD,k);
        rs=merge(t[x].rson,t[y].rson,(lx+t[t[x].lson].val)%MOD,rx,(ly+t[t[y].lson].val)%MOD,ry,k);
        t[p].val=(t[ls].val+t[rs].val)%MOD;
        return p;
    }

    void getans(int p,int l,int r){
        if(!p) return;
        if(l==r){
            d[l]=t[p].val;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        getans(ls,l,mid);
        getans(rs,mid+1,r);
    }
#undef ls
#undef rs
}sg;

namespace Tree{

    void dfs1(int u){
        if(!ch[u][0]){
            sg.insert(rt[u],1,dtot,val[u]);
            return;
        }
        if(!ch[u][1]){
            dfs1(ch[u][0]);
            rt[u]=rt[ch[u][0]];
            return;
        }
        dfs1(ch[u][0]);
        dfs1(ch[u][1]);
        rt[u]=sg.merge(rt[ch[u][0]],rt[ch[u][1]],0,0,0,0,val[u]);
    }

}using namespace Tree;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int fa;
        cin>>fa;
        if(ch[fa][0]) ch[fa][1]=i;
        else ch[fa][0]=i;
    }
    for(int i=1;i<=n;i++){
        cin>>val[i];
        if(ch[i][0]) val[i]=val[i]*INV%MOD;
        else b[++dtot]=val[i];
    }
    sort(b+1,b+1+dtot);
    for(int i=1;i<=n;i++){
        if(!ch[i][0]) val[i]=lower_bound(b+1,b+1+dtot,val[i])-b;
    }
    dfs1(1);
    sg.getans(rt[1],1,dtot);
    for(int i=1;i<=dtot;i++){
        ans=(ans+i*b[i]%MOD*d[i]%MOD*d[i]%MOD)%MOD;
    }
    cout<<ans;

    return 0;
}
