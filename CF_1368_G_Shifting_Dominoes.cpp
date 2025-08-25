#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MN=4e5+15;
int n,m,ans;
int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0}; 
vector<int> mp[MN];
vector<int> adj[MN];

struct SL{
    #define ll long long
    #define ls p<<1
    #define rs p<<1|1
    struct scanline{
        ll l,r,h;
        int dat;
        bool operator <(const scanline &s)const{return h<s.h;}
    }line[MN<<1];
    struct segtree{
        int l,r,sum;
        ll len;
    }t[MN<<2];
    ll x[MN];
    void build(int p,int l,int r){
        t[p].l=l; t[p].r=r; t[p].len=t[p].sum=0;
        if(l==r) return;
        int mid=l+r>>1;
        build(ls,l,mid); build(rs,mid+1,r);
    }
    void pushup(int p){
        if(t[p].sum) t[p].len=x[t[p].r+1]-x[t[p].l];
        else t[p].len=t[ls].len+t[rs].len;
    }
    void edittree(int p,ll fl,ll fr,int c){
        int l=t[p].l,r=t[p].r;
        if(x[r+1]<=fl||x[l]>=fr) return;
        if(x[l]>=fl&&x[r+1]<=fr){
            t[p].sum+=c; pushup(p); return;
        }
        int mid=l+r>>1;
        if(x[mid]>=fl) edittree(ls,fl,fr,c);
        if(x[mid]<fr) edittree(rs,fl,fr,c);
        pushup(p);
    }
    #undef ls
    #undef rs
}scan;

namespace Tree{
    int dfn[MN],siz[MN],fa[MN],dtot;
    void dfs(int u,int pre){
        dfn[u]=++dtot; siz[u]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);           
            siz[u]+=siz[v];
        }
    }
}using namespace Tree;

int getch(char x){
    if(x=='R') return 0;
    if(x=='D') return 1;
    if(x=='L') return 2;
    return 3;
}
int getpos(int x,int y){return (x-1)*m+y;}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        mp[i].resize(m+1);
        for(int j=1;j<=m;j++){
            char x; cin>>x;
            mp[i][j]=getch(x);
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<4;k++){
                int nx=i+dx[k]*2,ny=j+dy[k]*2;
                if(nx<1||nx>n||ny<1||ny>m||mp[nx][ny]!=(k+2)%4) continue;
                adj[getpos(i,j)].push_back(getpos(nx,ny));
                fa[getpos(nx,ny)]=getpos(i,j);
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!dfn[getpos(i,j)]){ 
                int x=getpos(i,j);
                while(fa[x]) x=fa[x];
                dfs(x,0);
            }
        }
    }
    int Xtot=0,Ltot=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if((i+j)&1){
                int nx=i+dx[mp[i][j]],ny=j+dy[mp[i][j]]; 
                if(nx<1||nx>n||ny<1||ny>m) continue; 
                int xl=dfn[getpos(i,j)];
                int xr=xl+siz[getpos(i,j)]-1;
                int yl=dfn[getpos(nx,ny)];
                int yr=yl+siz[getpos(nx,ny)]-1;
                scan.x[++Xtot]=xl; scan.x[++Xtot]=xr+1;
                scan.line[++Ltot]={xl,xr+1,yl,+1};
                scan.line[++Ltot]={xl,xr+1,yr+1,-1};
            }
        }
    }
    sort(scan.line+1,scan.line+1+Ltot);
    sort(scan.x+1,scan.x+1+Xtot);
    int tot=unique(scan.x+1,scan.x+1+Xtot)-scan.x-1;
    scan.build(1,1,tot-1);
    for(int i=1;i<Ltot;i++){
        scan.edittree(1,scan.line[i].l,scan.line[i].r,scan.line[i].dat);
        ans+=scan.t[1].len*(scan.line[i+1].h-scan.line[i].h);
    }
    cout<<ans;
    return 0;
}
