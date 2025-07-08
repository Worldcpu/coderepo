#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,g[MN],f[MN],ans=1;
string s;

struct Segment{
#define ls t[p].lson
#define rs t[p].rson
    struct Node{
        int lson,rson;
    }t[MN*10];
    int tot,rt[MN];

    void modify(int &p,int l,int r,int pos){
        if(!p) p=++tot;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,l,mid,pos);
        else modify(rs,mid+1,r,pos);
    }

    int merge(int x,int y,int l,int r){
        if(!x||!y) return x+y;
        int p=++tot;
        if(l==r) return p;
        int mid=(l+r)>>1;
        ls=merge(t[x].lson,t[y].lson,l,mid);
        rs=merge(t[x].rson,t[y].rson,mid+1,r);
        return p;
    }

    bool query(int p,int l,int r,int fl,int fr){
        if(!p) return 0;
        if(l>=fl&&r<=fr) return 1;
        int mid=(l+r)>>1;
        if(mid>=fl&&query(ls,l,mid,fl,fr)) return 1;
        if(mid<fr&&query(rs,mid+1,r,fl,fr)) return 1;
        return 0;
    }

#undef ls
#undef rs
}sg;

struct SAM{
    int nxt[MN][26],fa[MN],mx[MN],len[MN],tot,lst;
    vector<int> adj[MN];

    void init(){
        tot=0;
        lst=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
    }

    int newnode(){
        int cur=++tot;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    int clone(int from){
        int cur=++tot;
        fa[cur]=fa[from];
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    void extend(int c){
        int cur=newnode();
        len[cur]=len[lst]+1;
        sg.modify(sg.rt[cur],1,n,mx[cur]=len[cur]);
        int p=lst;
        while(p!=-1&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(p==-1) fa[cur]=0;
        else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1) fa[cur]=q;
            else{
                int nq=clone(q);
                len[nq]=len[p]+1;
                while(p!=-1&&nxt[p][c]==q) nxt[p][c]=nq,p=fa[p];
                fa[q]=fa[cur]=nq;
            }
        }
        lst=cur;
    }

    void inittree(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
        }
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    void dfs1(int u){
        for(auto v:adj[u]){
            dfs1(v);
            sg.rt[u]=sg.merge(sg.rt[u],sg.rt[v],1,n);
            mx[u]=max(mx[u],mx[v]);
        }
    }

    void dfs2(int u){
        for(auto v:adj[u]){
            int q=g[u];  
            if(u==0){
                f[v]=1;
                g[v]=v;
            }
            if(!sg.query(sg.rt[q],1,n,mx[v]-len[v]+len[q],mx[v]-1)){
                f[v]=f[u];
                g[v]=g[u];
            }else g[v]=v,ans=max(ans,f[v]=f[u]+1);
            dfs2(v);
        }
    }

}sam;


int main(){
    cin>>n>>s;
    s=" "+s;
    sam.init();
    for(int i=1;i<=n;i++){
        sam.extend(s[i]-'a');
    }
    sam.inittree();
    sam.dfs1(0);
    sam.dfs2(0);
    cout<<ans;
    return 0;
}
