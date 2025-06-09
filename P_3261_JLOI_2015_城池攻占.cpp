#include<bits/stdc++.h>
#include <cmath>
#define int long long
using namespace std;
constexpr int MN=3e5+15;
int n,m,ans[MN],h[MN],fa[MN],die[MN],dep[MN],a[MN],v[MN],s[MN],c[MN];

namespace MergeHeap{
#define ls(x) t[x].lson
#define rs(x) t[x].rson

    struct Node{
        int lson,rson,dis,val,add,tim;
    }t[MN];
    int rt[MN];

    void pushdown(int p){
        if(t[p].add==0&&t[p].tim==1) return;
        if(ls(p)){
            t[ls(p)].tim*=t[p].tim;
            t[ls(p)].add*=t[p].tim;
            t[ls(p)].add+=t[p].add;
            t[ls(p)].val*=t[p].tim;
            t[ls(p)].val+=t[p].add;
        }
        if(rs(p)){
            t[rs(p)].tim*=t[p].tim;
            t[rs(p)].add*=t[p].tim;
            t[rs(p)].add+=t[p].add;
            t[rs(p)].val*=t[p].tim;
            t[rs(p)].val+=t[p].add;
        }
        t[p].add=0;
        t[p].tim=1;
    }

    int merge(int x,int y){
        if(!x||!y) return x+y;
        pushdown(x);
        pushdown(y);
        if(t[x].val>t[y].val) swap(x,y);
        t[x].rson=merge(t[x].rson,y);
        if(t[ls(x)].dis<t[rs(x)].dis) swap(ls(x),rs(x));
        t[x].dis=t[ls(x)].dis+1;
        return x;
    }
}using namespace MergeHeap;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        rt[i]=-1;
    }
    t[0].dis=-1;
    dep[1]=1;
    for(int i=2;i<=n;i++){
        cin>>fa[i]>>a[i]>>v[i];
        dep[i]=dep[fa[i]]+1;
    }
    for(int i=1;i<=m;i++){
        cin>>s[i]>>c[i];
        t[i].tim=1;
        t[i].val=s[i];
        if(rt[c[i]]==-1) rt[c[i]]=i;
        else rt[c[i]]=merge(rt[c[i]],i);
    }
    for(int i=n;i>=1;i--){
        while(rt[i]!=-1){
            if(t[rt[i]].val<h[i]){
                die[rt[i]]=i;
                pushdown(rt[i]);
                if(!ls(rt[i])) rt[i]=-1;
                else rt[i]=merge(ls(rt[i]),rs(rt[i]));
            }else break;
        }
        if(i==1) break;
        if(rt[i]==-1) continue;
        if(a[i]) t[rt[i]].tim*=v[i],t[rt[i]].add*=v[i],t[rt[i]].val*=v[i];
        else t[rt[i]].add+=v[i],t[rt[i]].val+=v[i];
        pushdown(rt[i]);
        if(rt[fa[i]]==-1) rt[fa[i]]=rt[i];
        else rt[fa[i]]=merge(rt[fa[i]],rt[i]);
    }
    for(int i=1;i<=m;i++){
        ans[die[i]]++;
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }
    for(int i=1;i<=m;i++) cout<<dep[c[i]]-dep[die[i]]<<'\n';
    return 0;
}
