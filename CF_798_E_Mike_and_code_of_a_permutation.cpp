#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],tim[MN],ans[MN],tot;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r;
        pir val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=max(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=pir(tim[k],k);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    pir query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1;
        pir ret(0,0);
        if(mid>=fl) ret=query(ls,fl,fr);
        if(mid<fr) ret=max(ret,query(rs,fl,fr));
        return ret;
    }

}sg;

void dfs(int u){
    int t=tim[u];
    tim[u]=0;
    sg.modify(1,u,u);
    if(t!=n+1&&tim[t]) dfs(t);
    while("QWQ"){
        pir ret=sg.query(1,1,a[u]-1);
        if(ret.first<=u) break;
        dfs(ret.second);
    }
    ans[u]=++tot;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]!=-1) tim[a[i]]=i;
        if(a[i]==-1) a[i]=n+1;
    }
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        if(!tim[i]) tim[i]=n+1;
        sg.modify(1,i,i);
    }
    for(int i=1;i<=n;i++){
        if(!ans[i]) dfs(i);
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    return 0;
}