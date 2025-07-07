#include<bits/stdc++.h>
#include <cstdlib>
#define pir pair<int,int>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,m,q,pre[30][MN],ansl[MN],poss[MN];
string s,t[MN];

struct Segment{
#define ls t[p].lson
#define rs t[p].rson

    struct Node{
        int lson,rson;
        pir val;
    }t[MN<<2];
    int tot,rt[MN];

    void pushup(int p){
        t[p].val=max(t[ls].val,t[rs].val);
    }

    void update(int &p,int l,int r,int pos){
        if(!p)  p=++tot;
        if(l==r){
            t[p].val.first++;
            t[p].val.second=-l;
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) update(ls,l,mid,pos);
        else update(rs,mid+1,r,pos);
        pushup(p);
    }

    int merge(int x,int y,int l,int r){
        if(!x||!y) return x+y;
        int p=++tot;
        if(l==r){
            t[p].val.first=t[x].val.first+t[y].val.first;
            t[p].val.second=-l;
            return p;
        }
        int mid=(l+r)>>1;
        ls=merge(t[x].lson,t[y].lson,l,mid);
        rs=merge(t[x].rson,t[y].rson,mid+1,r);
        pushup(p);
        return p;
    }

    pir query(int p,int l,int r,int fl,int fr){
        if(!p) return pir(0,0);
        if(l>=fl&&r<=fr){
            return t[p].val;
        }
        int mid=(l+r)>>1;
        pir ret={0,0};
        if(mid>=fl) ret=max(ret,query(ls,l,mid,fl,fr));
        if(mid<fr) ret=max(ret,query(rs,mid+1,r,fl,fr));
        return ret;
    }

#undef ls
#undef rs
}sg;


struct gySAM{
    int nxt[MN][26],fa[MN],len[MN],tot;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++) adj[i].clear();
        tot=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
    }

    gySAM(){
        init();
    }

    int newnode(int lst,int id){
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

    int extend(int c,int lst,int id){
        if(nxt[lst][c]){
            int p=nxt[lst][c];
            if(len[p]==len[lst]+1) return p;
            else{
                int q=clone(p);
                len[q]=len[lst]+1;
                while(lst!=-1&&nxt[lst][c]==p) nxt[lst][c]=q,lst=fa[lst];
                fa[p]=q;
                return q;
            }
        }
        int cur=newnode(lst,id);
        len[cur]=len[lst]+1;
        while(lst!=-1&&!nxt[lst][c]) nxt[lst][c]=cur,lst=fa[lst];
        if(lst==-1) fa[cur]=0;
        else{
            int p=nxt[lst][c];
            if(len[p]==len[lst]+1) fa[cur]=p;
            else{
                int q=clone(p);
                len[q]=len[lst]+1;
                while(lst!=-1&&nxt[lst][c]==p) nxt[lst][c]=q,lst=fa[lst];
                fa[p]=fa[cur]=q;
            }
        }
        return cur;
    }

    void inittree(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
        }
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            pre[0][v]=u;
            sg.rt[u]=sg.merge(sg.rt[u],sg.rt[v],1,m);
        }
    }

    void insert(string s,int id){
        int len=s.length();
        s=" "+s;
        int lst=0;
        for(int i=1;i<=len;i++){
            lst=extend(s[i]-'a',lst,id);
            sg.update(sg.rt[lst],1,m,id);
        }
    }

    void clac(){
        int p=0;
        for(int i=1,lcs=0;i<=n;i++){
            int k=s[i]-'a';
            if(nxt[p][k]){
                lcs++;
                p=nxt[p][k];
            }else{
                while(p!=-1&&!nxt[p][k]){
                    p=fa[p];
                }
                if(p==-1){
                    lcs=0;
                    p=0;
                }else lcs=len[p]+1,p=nxt[p][k];
            }
            ansl[i]=lcs;
            poss[i]=p;
        }
    }

}sam;

signed main(){
    cin>>s>>m;
    n=s.length();
    s=" "+s;
    for(int i=1;i<=m;i++){
        cin>>t[i];
        sam.insert(t[i],i);
    }
    sam.inittree();
    sam.dfs(0);
    for(int i=1;i<=20;i++){
        for(int j=1;j<=sam.tot;j++){
            pre[i][j]=pre[i-1][pre[i-1][j]];
        }
    }
    sam.clac();
    cin>>q;
    while(q--){
        int l,r,fl,fr;
        cin>>fl>>fr>>l>>r;
        if(r-l+1>ansl[r]){
            cout<<fl<<" 0\n";
            continue;
        }
        int cur=poss[r];
        for(int i=20;i>=0;i--){
            if(sam.len[pre[i][cur]]>=r-l+1){
                cur=pre[i][cur];
            }
        }
        pir ans=sg.query(sg.rt[cur],1,m,fl,fr);
        if(ans.first==0) ans.second=-fl;
        cout<<-ans.second<<" "<<ans.first<<'\n';
    }

    return 0;
}
