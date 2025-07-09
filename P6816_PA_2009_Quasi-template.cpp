#include<bits/stdc++.h>
#define pir pair<int,int>
#define ll long long
#define ull unsigned long long
using namespace std;
constexpr int MN=4e5+15;
struct Query{
    int l,r,v;
};
int n,rt[MN],bd[MN],mx[MN],mn[MN];
ll ans1;
pir ans2;
string s;
vector<Query> vec[MN];

struct Segment{
#define ls t[p].lson
#define rs t[p].rson
    struct Node{
        int lson,rson,mx,lp,rp;
    }t[MN*20];
    int tot;

    void pushup(int p){
        if(!ls){
            t[p].mx=t[rs].mx,t[p].lp=t[rs].lp,t[p].rp=t[rs].rp;
            return;
        }
        if(!rs){
            t[p].mx=t[ls].mx,t[p].lp=t[ls].lp,t[p].rp=t[ls].rp;
            return;
        }
        t[p].mx=max({t[ls].mx,t[rs].mx,t[rs].lp-t[ls].rp});
        t[p].lp=t[ls].lp,t[p].rp=t[rs].rp;
    }

    void modify(int &p,int l,int r,int pos){
        if(!p) p=++tot;
        if(l==r) return t[p].lp=t[p].rp=pos,void(0);
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,l,mid,pos);
        else modify(rs,mid+1,r,pos);
        pushup(p);
    }

    int merge(int p,int x){
        if(!p||!x) return p|x;
        ls=merge(ls,t[x].lson);
        rs=merge(rs,t[x].rson);
        pushup(p);
        return p;
    }
#undef ls
#undef rs
}sg;

struct Segmentt{
#define ls p<<1
#define rs p<<1|1
    struct Node{
        int l,r,mx,mc,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
        t[p].mc=0;
        if(t[ls].mx>=t[p].mx){
            t[p].mc+=t[ls].mc;
        }
        if(t[rs].mx>=t[p].mx){
            t[p].mc+=t[rs].mc;
        }
    }

    void doadd(int p,int k){
        t[p].mx+=k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
            return;
        }
    }

    void build(int p,int l,int r){
        t[p]={l,r,0,r-l+1,0};
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
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

    int find(int p){
        if(t[p].l==t[p].r) return t[p].l;
        pushdown(p);
        if(t[rs].mx>=2) return find(rs);
        else return find(ls);
    }

#undef ls
#undef rs
}sgg;

namespace Hash{
    constexpr ull base=131;
    ull hsh[MN],pw[MN];

    void inithsh(){
        pw[0]=1;
        for(int i=1;i<=n;i++){
            pw[i]=pw[i-1]*base;
            hsh[i]=hsh[i-1]*base+s[i];
        }
    }

    ull gethsh(int l,int r){
        return hsh[r]-hsh[l-1]*pw[r-l+1];
    }

    int lcp(int x,int y){
        int l=1,r=min(n-x+1,n-y+1),ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(gethsh(x,x+mid-1)==gethsh(y,y+mid-1)) ans=mid,l=mid+1;
            else r=mid-1;
        }
        return ans;
    }
}using namespace Hash;

namespace SAM{
    int nxt[MN][26],fa[MN],len[MN],pos[MN],tot,lst;
    vector<int> adj[MN];

    void initsam(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
            fa[i]=len[i]=pos[i]=bd[i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        tot=lst=1;
    }

    inline void expand(int c,int id){
        int cur=++tot;
        pos[cur]=id;
        len[cur]=len[lst]+1;
        int p=lst;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int nq=++tot;
                len[nq]=len[p]+1,fa[nq]=fa[q];
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[q]=fa[cur]=nq;
                while(nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }

    inline void inittree(){
        for(int i=2;i<=tot;i++) adj[fa[i]].push_back(i);
    }

}using namespace SAM;

void addquery(int l1,int r1,int l2,int r2){
    vec[l1].push_back({l2,r2,1});
    vec[r1+1].push_back({l2,r2,-1});
}

void dfspre(int u){
    int bod=bd[u];
    if(pos[u]) bd[u]=pos[u],sg.modify(rt[u],1,n,pos[u]);
    for(auto v:adj[u]){
        bd[v]=bd[u];
        dfspre(v);
        rt[u]=sg.merge(rt[u],rt[v]);
    }
    int fp=sg.t[rt[u]].lp,nd=sg.t[rt[u]].mx;
    int L=max(len[fa[u]]+1,max(nd,fp-bod)),R=len[u];
    if(L<=R) addquery(fp,fp,fp-R+1,fp-L+1);
}

void dfssuf(int u){
    mx[u]=0,mn[u]=1e9;
    int bod=bd[u];
    if(pos[u]){
        mx[u]=mn[u]=pos[u];
        bd[u]=pos[u];
    }
    for(auto v:adj[u]){
        bd[v]=bd[u];
        dfssuf(v);
        mx[u]=max(mx[u],mx[v]);
        mn[u]=min(mn[u],mn[v]);
    }
    int lp=mx[u],fp=mn[u];
    int L=max(len[fa[u]]+1,fp-bod),R=len[u];
    if(L<=R) addquery(n-(lp-L+1)+1,n-(lp-R+1)+1,n-lp+1,n-lp+1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    cin>>s;
    n=s.length();
    s=" "+s;
    inithsh();
    initsam();
    for(int i=1;i<=n;i++){
        expand(s[i]-'a',i);
    }
    inittree();
    dfspre(1);
    initsam();
    for(int i=n;i>=1;i--){
        expand(s[i]-'a',n-i+1);
    }
    inittree();
    dfssuf(1);
    sgg.build(1,1,n);
    ans2=pir(0,n+1);
    for(int i=1;i<=n;i++){
        for(auto pt:vec[i]) sgg.modify(1,pt.l,pt.r,pt.v);
        if(sgg.t[1].mx>=2){
            ans1+=sgg.t[1].mc;
            int l=sgg.find(1),r=i;
            if(ans2.second-ans2.first>r-l) ans2=pir(l,r);
            else if(ans2.second-ans2.first==r-l){
                int lcpp=lcp(ans2.first,l);
                if(lcpp<r-l+1&&s[ans2.first+lcpp]>s[l+lcpp]) ans2=pir(l,r);
            }
        }
    }
    cout<<ans1<<'\n';
    for(int i=ans2.first;i<=ans2.second;i++){
        cout<<s[i];
    }
    return 0;
}
