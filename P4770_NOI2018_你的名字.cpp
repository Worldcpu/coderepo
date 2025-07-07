#include<bits/stdc++.h>
#define ll long long
#define LOJ
using namespace std;
constexpr int MN=5e6+15;
int n,m,q,lcsl[MN];
string s,t;

struct Segment{
#define ls t[p].lson
#define rs t[p].rson
    struct Node{
        int lson,rson,val;
    }t[MN*10];
    int tot,rt[MN];

    void modify(int &p,int l,int r,int pos){
        if(!p) p=++tot;
        t[p].val++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,l,mid,pos);
        else modify(rs,mid+1,r,pos);
    }

    int merge(int x,int y,int l,int r){
        if(!x||!y) return x+y;
        int p=++tot;
            t[p].val=t[x].val+t[y].val;
        if(l==r){
            return p;
        }
        int mid=(l+r)>>1;
        ls=merge(t[x].lson,t[y].lson,l,mid);
        rs=merge(t[x].rson,t[y].rson,mid+1,r);
        return p;
    }

    int query(int p,int l,int r,int fl,int fr){
        if(!p) return 0;
        if(l>=fl&&r<=fr) return t[p].val;
        int mid=(l+r)>>1;
        int ret=0;
        if(mid>=fl) ret+=query(ls,l,mid,fl,fr);
        if(mid<fr) ret+=query(rs,mid+1,r,fl,fr);
        return ret;
    }
}sg;

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],id[MN],lst,tot;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++) fa[i]=len[i]=id[i]=0,adj[i].clear();
        tot=lst=0;
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
        id[cur]=id[from];
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    void extend(int c,int pos){
        int cur=newnode();
        len[cur]=len[lst]+1;
        id[cur]=pos;
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
        for(int i=1;i<=tot;i++) adj[fa[i]].push_back(i);
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            sg.rt[u+1]=sg.merge(sg.rt[u+1],sg.rt[v+1],1,n);
        }
    }
}sam1,sam2;

void getlcs(int l,int r){
    int p=0,lcs=0;
    for(int i=1;i<=m;i++){
        int k=t[i]-'a';
        while(1){
            if(sam1.nxt[p][k]&&sg.query(sg.rt[sam1.nxt[p][k]+1],1,n,l+lcs,r)){
                p=sam1.nxt[p][k];
                lcs++;
                break;
            }
            if(!lcs) break;
            lcs--;
            if(lcs==sam1.len[sam1.fa[p]]) p=sam1.fa[p];
        }
        lcsl[i]=lcs;
    }
}

int main(){
#ifdef LOJ
    freopen("name.in","r",stdin);
    freopen("name.out","w",stdout);
#endif
    cin>>s;
    n=s.length();
    s=" "+s;
    sam1.init();
    for(int i=1;i<=n;i++){
        sam1.extend(s[i]-'a',i);
        sg.modify(sg.rt[sam1.lst+1],1,n,i);
    }
    sam1.inittree();
    sam1.dfs(0);
    cin>>q;
    while(q--){
        int fl,fr;
        cin>>t>>fl>>fr;
        m=t.length();
        t=" "+t;
        sam2.init();
        for(int i=1;i<=m;i++){
            sam2.extend(t[i]-'a',i);
        }
        getlcs(fl,fr);
        ll ans=0;
        for(int i=1;i<=sam2.tot;i++){
            ans+=max(sam2.len[i]-max(lcsl[sam2.id[i]],sam2.len[sam2.fa[i]]),0);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
