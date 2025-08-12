#include<bits/stdc++.h>
#include <queue>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
struct Node{
    int l,r,c,t;
}a[MN];
int n,m,f[MN],ans=INF;
bool vis[MN];
priority_queue<pir,vector<pir>,greater<pir>> q;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mn[2];
    }t[MN<<2];

    void pushup(int p){
        t[p].mn[0]=min(t[ls].mn[0],t[rs].mn[0]);
        t[p].mn[1]=min(t[ls].mn[1],t[rs].mn[1]);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].mn[0]=t[p].mn[1]=INF;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modify(int p,int pos,int x,int y){
        if(t[p].l==t[p].r){
            t[p].mn[0]=x-y;
            t[p].mn[1]=x+y;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,x,y);
        else modify(rs,pos,x,y);
        pushup(p);
    }

    void update(int p,int fl,int fr,int op,int v,int w){
        if(t[p].mn[op]>v) return;
        if(t[p].l==t[p].r){
            f[t[p].l]=w+a[t[p].l].c;
            q.push(pir(f[t[p].l],t[p].l));
            t[p].mn[0]=t[p].mn[1]=INF;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) update(ls,fl,fr,op,v,w);
        if(mid<fr) update(rs,fl,fr,op,v,w);
        pushup(p);
    }

    #undef ls
    #undef rs
}sg;

bool cmp(Node x,Node y){
    return x.t<y.t;
}

void dijkstra(){
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=m;i++){
        if(a[i].l==1){
            f[i]=a[i].c;
            q.push(pir(f[i],i));
            sg.modify(1, i, INF, 0);
        }else sg.modify(1, i, a[i].l, a[i].t);
    }
    while(!q.empty()){
        auto fr=q.top();
        q.pop();
        int u=fr.second;
        if(vis[u]) continue;
        vis[u]=1;
        sg.update(1,1,u-1,0,a[u].r-a[u].t+1,f[u]);
        sg.update(1,u+1,m,1,a[u].r+a[u].t+1,f[u]);
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i].t>>a[i].l>>a[i].r>>a[i].c;
    }
    sort(a+1,a+1+m,cmp);
    sg.build(1,1,m);
    dijkstra();
    for(int i=1;i<=m;i++){
        if(a[i].r==n){
            ans=min(ans,f[i]);
        }
    }
    if(ans>=INF) cout<<-1;
    else cout<<ans;

    return 0;
}