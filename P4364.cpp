#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int cnt[MN],a[MN],n,ans[MN];
double K;
vector<int> adj[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mn,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].mn=min(t[ls].mn,t[rs].mn);
    }

    void doadd(int p,int k){
        t[p].mn+=k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mn=l;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int k){
        if(t[p].l==t[p].r){
            return t[p].mn>=k?t[p].l:t[p].l+1;
        }
        pushdown(p);
        if(t[rs].mn>=k) return query(ls,k);
        else return query(rs,k);
    }
}sg;

namespace Tree{
    int siz[MN],fa[MN];


}using namespace Tree;

bool cmp(int x,int y){
    return x>y;
}

int main(){
    cin>>n>>K;
    list<int> lst;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        fa[i]=(int)floor(1.0*i/K);
        siz[i]=1;
    }
    for(int i=n;i>=1;i--){
        siz[fa[i]]+=siz[i];
    }
    sort(a+1,a+1+n,cmp);
    for(int i=n-1;i>=1;i--){
        if(a[i]==a[i+1]){
            cnt[i]=cnt[i+1]+1;
        }else cnt[i]=0;
    }
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        if(fa[i]&&fa[i]!=fa[i-1]){
            sg.modify(1,ans[fa[i]],n,siz[fa[i]]-1);
        }
        int x=sg.query(1,siz[i]);
        x+=cnt[x];
        cnt[x]++;
        x-=cnt[x]-1;
        ans[i]=x;
        sg.modify(1,x,n,-siz[i]);
    }
    for(int i=1;i<=n;i++){
        cout<<a[ans[i]]<<' ';
    }
    return 0;
}