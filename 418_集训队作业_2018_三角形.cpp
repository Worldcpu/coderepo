#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=2e5+15;
struct Node{
    ll x,y;
    int id;

    Node(ll xx=0,ll yy=0,int idd=0){
        x=xx,y=yy,id=idd;
    }

    friend Node operator+(const Node &x,const Node &y){
        return (Node){x.x+y.x,max(x.y,x.x+y.y),x.id};
    }

    friend bool operator<(const Node &x,const Node &y){
        ll y1=(x+y).y,y2=(y+x).y;
        if(y1!=y2) return y1<y2;
        if(x.x!=y.x) return x.x<y.x;
        if(x.y!=y.y) return x.y<y.y;
        return x.id<y.id;
    }
}a[MN];
int n,rt[MN],seq[MN],qtot;
ll ans[MN],w[MN],sumw[MN];
bool vis[MN];
vector<int> adj[MN],G[MN];
set<Node> st;

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct SNode{
        int lson,rson;
        Node val;
    }t[MN*30];
    int tot;

    void pushup(int p){
        t[p].val=t[t[p].lson].val + t[t[p].rson].val;
    }

    void modify(int &p,int l,int r,int pos){
        if(!p) p=++tot;
        if(l==r){
            t[p].val=a[l];
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) modify(t[p].lson,l,mid,pos);
        else modify(t[p].rson,mid+1,r,pos);
        pushup(p);
    }

    int merge(int x,int y){
        if(!x||!y) return x+y;
        t[x].lson=merge(t[x].lson,t[y].lson);
        t[x].rson=merge(t[x].rson,t[y].rson);
        pushup(x);
        return x;
    }

}sg;

namespace DSU{
    int pre[MN];

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

}using namespace DSU;

namespace Tree{
    int fa[MN];
    
    void dfs1(int u){
        vis[u]=1;
        seq[u]=++qtot;
        for(auto v:G[u]){ 
            dfs1(v);
        }
    }

    void dfs2(int u){
        sg.modify(rt[u],1,n,seq[u]);
        for(auto v:adj[u]){
            dfs2(v);
            rt[u]=sg.merge(rt[u],rt[v]);
        }
        ans[u]=sg.t[rt[u]].val.y;
    }

}using namespace Tree;

int main(){
    int qwq;
    cin>>qwq>>n;
    for(int i=2;i<=n;i++){
        int f;cin>>f;
        Tree::fa[i]=f;
        adj[f].push_back(i);
    }
    for(int i=1;i<=n;i++){
        cin>>w[i];
        sumw[ Tree::fa[i] ]+=w[i];       
        pre[i]=i;
    }
    for(int i=1;i<=n;i++){
        a[i]=Node(sumw[i]-w[i],sumw[i],i);
        st.insert(a[i]);
    }
    for(int i=1;i<=n;i++){
        auto tp=(*st.begin());
        st.erase(st.begin());
        if(tp.id==1||vis[ Tree::fa[tp.id] ]){ 
            Tree::dfs1(tp.id);
        }else{
            int u=root(Tree::fa[tp.id]);
            st.erase(a[u]);
            a[u]=a[u]+a[tp.id];
            st.insert(a[u]);
            G[u].push_back(tp.id);
            pre[tp.id]=u;
        }
    }
    for(int i=1;i<=n;i++){
        a[seq[i]]=Node(sumw[i]-w[i],sumw[i],i);
    }
    Tree::dfs2(1);
    for(int i=1;i<=n;i++){
        cout<<ans[i]+w[i]<<' ';
    }
    return 0;
}
