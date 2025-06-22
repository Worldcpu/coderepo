#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
constexpr int MX=1e5+15,MN=1e6+15,MOD=1e9+7;
struct Edge{
    int v,w;
};
int n,m,S,T,pre[MN+15];
ull pw1[MN+15],pw2[MN+15];
bool vis[MN];
vector<ll> ans;
vector<Edge> adj[MN];

struct Segment{
#define ls t[p].lson
#define rs t[p].rson

    struct Node{
        int lson,rson;
        ll sum;
        ull hsh1,hsh2;
    }t[MN<<2];
    int tot=0,rt[MN];

    void pushup(int p){
        t[p].sum=t[ls].sum+t[rs].sum;
        t[p].hsh1=(t[ls].hsh1+t[rs].hsh1)%MOD;
        t[p].hsh2=t[ls].hsh2+t[rs].hsh2;
    }

    int build(int l,int r,int x){
        int p=++tot;
        if(l==r){
            t[p].sum=x;
            t[p].hsh1=pw1[l]*x;
            t[p].hsh2=pw2[l]*x;
            return p;
        }
        int mid=(l+r)>>1;
        ls=build(l,mid,x);
        rs=build(mid+1,r,x);
        pushup(p);
        return p;
    }

    ll querysum(int p,int l,int r,int fl,int fr){
        if(l>fr||r<fl) return 0;
        if(l>=fl&&r<=fr) return t[p].sum;
        int mid=(l+r)>>1;
        return querysum(ls,l,mid,fl,fr)+querysum(rs,mid+1,r,fl,fr);
    }

    ll query(int p,int l,int r,int pos){
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(pos>mid) return query(rs,mid+1,r,pos);
        if(querysum(ls,l,mid,pos,mid)==mid-pos+1) return query(rs,mid+1,r,mid+1);
        else return query(ls,l,mid,pos);
    }

    int modify(int lst,int l,int r,int pos){
        int p=++tot;
        t[p].lson=t[lst].lson,t[p].rson=t[lst].rson;
        if(l==r){
            t[p].sum=1;
            t[p].hsh1=pw1[l];
            t[p].hsh2=pw2[l];
            return p;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) ls=modify(t[lst].lson,l,mid,pos);
        else rs=modify(t[lst].rson,mid+1,r,pos);
        pushup(p);
        return p;
    }

    int update0(int x,int y,int l,int r,int fl,int fr){
        if(l>fr||r<fl) return x;
        if(l>=fl&&r<=fr) return y;
        int p=++tot;
        int mid=(l+r)>>1;
        ls=update0(t[x].lson,t[y].lson,l,mid,fl,fr);
        rs=update0(t[x].rson,t[y].rson,mid+1,r,fl,fr);
        pushup(p);
        return p;
    }

    int add(int pp,int w){
        int pos=query(pp,0,MX,w);
        int p=modify(pp,0,MX,pos);
        if(pos==w) return p;
        else return update0(p,rt[0],0,MX,w,pos-1);
    }

    bool issame(int x,int y){
        return t[x].sum==t[y].sum&&t[x].hsh1==t[y].hsh1&&t[x].hsh2==t[y].hsh2;
    }

    bool compare(int x,int y,int l,int r){
        if(l==r) return t[x].sum<=t[y].sum;
        int mid=(l+r)>>1;
        if(issame(t[x].rson,t[y].rson)) return compare(t[x].lson,t[y].lson,l,mid);
        else return compare(t[x].rson,t[y].rson,mid+1,r);
    }

#undef ls
#undef rs
}sg;

struct Heap{
    int rt[MN],id[MN],dis[MN],lson[MN],rson[MN];
    int siz,cnt,root;

    int merge(int x,int y){
        if(!x||!y) return x^y;
        if(sg.compare(rt[y],rt[x],0,MX)) swap(x,y);
        rson[x]=merge(rson[x],y);
        if(dis[rson[x]]>dis[lson[x]]) swap(lson[x],rson[x]);
        dis[x]=dis[lson[x]]+1;
        return x;
    }

    void push(int x,int y){
        siz++;
        cnt++;
        id[cnt]=x;
        rt[cnt]=y;
        root=merge(root,cnt);
    }

    void pop(){
        siz--;
        root=merge(lson[root],rson[root]);
    }

    int top(){
        return id[root];
    }

    bool isempty(){
        return siz==0;
    }
}q;

void init(){
    pw1[0]=pw2[0]=1;
    for(int i=1;i<MN;i++) pw1[i]=pw1[i-1]*2%MOD,pw2[i]=pw2[i-1]*1313131%MOD;
}

void dij(){
    int tmp;
    tmp=sg.build(0,MX,1);
    for(int i=1;i<=n;i++) sg.rt[i]=tmp;
    sg.rt[0]=sg.rt[S]=sg.build(0,MX,0);
    q.push(S,sg.rt[S]);
    while(!q.isempty()){
        int u=q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
            if(vis[e.v]) continue;
            int np=sg.add(sg.rt[u],e.w);
            if(sg.compare(sg.rt[e.v],np,0,MX)) continue;
            sg.rt[e.v]=np,pre[e.v]=u;
            q.push(e.v,sg.rt[e.v]);
        }
    }
    if(sg.rt[T]==tmp){
        cout<<-1;
        return;
    }
    cout<<sg.t[sg.rt[T]].hsh1<<'\n';
    for(int i=T;i!=pre[S];i=pre[i]) ans.push_back(i);
    cout<<ans.size()<<'\n';
    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i]<<" ";
    }
    
}

signed main(){
    init();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    cin>>S>>T;
    dij();
    return 0;
}
