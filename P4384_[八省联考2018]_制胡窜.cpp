#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,q,pos[MN];
string s;

struct Segment{
    struct Node{
        int l,r,mn,mx,ans;
        Node friend operator +(Node a,Node b){
            if(!a.ans&&!b.ans) return {a.l,b.r,0,0,0};
            if(!a.ans) return {a.l,b.r,b.mn,b.mx,b.ans+(a.r-a.l+1)*(b.r-b.mn+1)};
            if(!b.ans) return {a.l,b.r,a.mn,a.mx,a.ans+(a.mx-a.l+1)*(b.r-b.l+1)};
            return {a.l,b.r,a.mn,b.mx,a.ans+b.ans+(a.mx-a.l+1)*(b.r-b.l+1)+(a.r-a.mx)*(b.r-b.mn+1)};
        }
    }t[MN*15];
    int tot,rt[MN],ls[MN*15],rs[MN*15];

    void modify(int &p,int l,int r,int pos){
        p=++tot;
        t[p]={l,r,pos,pos,(pos-l+1)*(r-pos+1)};
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls[p],l,mid,pos);
        else modify(rs[p],mid+1,r,pos);
    }

    int merge(int x,int y,int l,int r){
        if(!x||!y) return x+y;
        int p=++tot;
        int mid=(l+r)>>1;
        ls[p]=merge(ls[x],ls[y],l,mid);
        rs[p]=merge(rs[x],rs[y],mid+1,r);
        t[p]=(ls[p]?t[ls[p]]:(Node){l,mid,0,0,0})+(rs[p]?t[rs[p]]:(Node){mid+1,r,0,0,0});
        return p;
    }

    Node query(int p,int l,int r,int fl,int fr){
        if(l>=fl&&r<=fr) return p?t[p]:(Node){l,r,0,0,0};
        int mid=(l+r)>>1;
        if(mid>=fr) return query(ls[p],l,mid,fl,fr);
        if(mid<fl) return query(rs[p],mid+1,r,fl,fr);
        return query(ls[p],l,mid,fl,fr)+query(rs[p],mid+1,r,fl,fr);
    }
}sg;

struct SAM{
    int nxt[MN][10],len[MN],fa[MN],pre[31][MN],stot,lst;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=stot;i++){
            fa[i]=len[i]=0;
            for(int j=0;j<=30;j++) pre[j][i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        stot=lst=1;
    }

    void expand(int c){
        int cur=++stot;
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
                int nq=++stot;
                len[nq]=len[p]+1;
                fa[nq]=fa[q];
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[q]=fa[cur]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }

    void initpre(){
        for(int i=1;i<=stot;i++) pre[0][i]=fa[i];
        for(int i=1;i<=30;i++){
            for(int j=2;j<=stot;j++){
                pre[i][j]=pre[i-1][pre[i-1][j]];
            }
        }
        for(int i=2;i<=stot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            sg.rt[u]=sg.merge(sg.rt[u],sg.rt[v],1,n);
        }
    }
}sam;

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q>>s;
    s=" "+s;
    sam.init();
    for(int i=1;i<=n;i++){
        sam.expand(s[i]-'0');
        pos[i]=sam.lst;
        sg.modify(sg.rt[pos[i]],1,n,i);
    }
    sam.initpre();
    sam.dfs(1);
    while(q--){
        int l,r;
        cin>>l>>r;
        int now=pos[r],slen=r-l+1;
        for(int i=30;i>=0;i--){
            if(sam.pre[i][now]&&sam.len[sam.pre[i][now]]>=slen) 
                now=sam.pre[i][now];
        }
        auto tmp=sg.t[sg.rt[now]];
        int p=tmp.mn,q=tmp.mx-slen+1;
        int ans=(n-p)*(n-p-1)/2+(q-1)*(q-2)/2;
        if(p<q) ans-=(q-p)*(q-p-1)/2;
        if(n>slen+1) ans+=sg.query(sg.rt[now],1,n,slen+1,n-1).ans;
        if(n>slen+p) ans-=sg.query(sg.rt[now],1,n,slen+p,n-1).ans;
        if(q>slen+1) ans-=sg.query(sg.rt[now],1,n,slen+1,q-1).ans;
        if(q>slen+p) ans+=sg.query(sg.rt[now],1,n,slen+p,q-1).ans;
        cout<<ans<<'\n';
    }
    return 0;
}
