#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
constexpr int MN=4e5+15;
struct Edge{
    int x,y;
}e[MN];
int n,m,K;
vector<int> t[MN<<2];

struct DSU{

    struct{
        int x,y,add;
    }s[MN];

    int pre[MN],siz[MN],top;

    DSU(){
        for(int i=1;i<MN;i++){
            pre[i]=i;
            siz[i]=1;
        }
    }

    int root(int x){
        if(pre[x]==x) return x;
        else return root(pre[x]);
    }

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(siz[rx]>siz[ry]) swap(rx,ry);
        s[++top]={rx,ry,siz[rx]==siz[ry]};
        pre[rx]=ry;
        if(siz[rx]==siz[ry]) siz[ry]++;
    }
}dsu;

void update(int p,int l,int r,int fl,int fr,int x){
    if(l>=fl&&r<=fr){
        t[p].push_back(x);
        return;
    }
    int mid=(l+r)>>1;
    if(mid>=fl) update(ls,l,mid,fl,fr,x);
    if(mid<fr) update(rs,mid+1,r,fl,fr,x);
}

void solve(int p,int l,int r){
    bool flag=1;
    int lsttop=dsu.top;
    for(auto awa:t[p]){
        int ru=dsu.root(e[awa].x),rv=dsu.root(e[awa].y);
        if(ru==rv){
            for(int k=l;k<=r;k++){
                cout<<"No\n";
            }
            flag=0;
            break;
        }
        dsu.merge(e[awa].x,e[awa].y+n);
        dsu.merge(e[awa].x+n,e[awa].y);
    }
    if(flag){
        if(l==r) cout<<"Yes\n";
        else{
            int mid=(l+r)>>1;
            solve(ls,l,mid);
            solve(rs,mid+1,r);
        }
    }
    while(dsu.top>lsttop){
        dsu.siz[dsu.pre[dsu.s[dsu.top].x]]-=dsu.s[dsu.top].add;
        dsu.pre[dsu.s[dsu.top].x]=dsu.s[dsu.top].x;
        dsu.top--;
    }
}

int main(){
    cin>>n>>m>>K;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>e[i].x>>e[i].y;
        cin>>l>>r;
        update(1,1,K,l+1,r,i);
    }
    solve(1,1,K);
    return 0;
}
