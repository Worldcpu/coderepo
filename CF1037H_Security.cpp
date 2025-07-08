#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,q,cnt,ans[MN];
string s,t;

struct Segment{
#define ls t[p].lson
#define rs t[p].rson

    struct Node{
        int lson,rson,val;
    }t[MN<<2];
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
        if(l==r) return p;
        int mid=(l+r)>>1;
        ls=merge(t[x].lson,t[y].lson,l,mid);
        rs=merge(t[x].rson,t[y].rson,mid+1,r);
        return p;
    }

    int query(int p,int l,int r,int fl,int fr){
        if(!p) return 0;
        if(l>=fl&&r<=fr){
            return t[p].val;
        }
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) ret+=query(ls,l,mid,fl,fr);
        if(mid<fr) ret+=query(rs,mid+1,r,fl,fr);
        return ret;
    }

}sg;

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],tot,lst;
    vector<int> adj[MN];

    void init(){
        tot=0;
        lst=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
    }

    SAM(){
        init();
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

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            sg.rt[u]=sg.merge(sg.rt[u],sg.rt[v],1,n);
        }
    }

    bool match(int fl,int fr,int len,int p){
        int c;
        if(len>m){
            c=-1;
        }else c=t[len]-'a';
        if(c>=0&&nxt[p][c]&&sg.query(sg.rt[nxt[p][c]],1,n,fl+len-1,fr)&&match(fl,fr,len+1,nxt[p][c])){
            ans[++cnt]=c;
            return 1;
        }
        for(int i=c+1;i<26;i++){
            if(nxt[p][i]&&sg.query(sg.rt[nxt[p][i]],1,n,fl+len-1,fr)){
                ans[++cnt]=i;
                return 1;
            }
        }
        return 0;
    }

}sam;

int main(){
    cin>>s;
    n=s.length();
    s=" "+s;
    for(int i=1;i<=n;i++){
        sam.extend(s[i]-'a');
        sg.modify(sg.rt[sam.lst],1,n,i);
    }
    sam.inittree();
    sam.dfs(0);
    cin>>q;
    while(q--){
        int fl,fr;
        cin>>fl>>fr>>t;
        m=t.length();
        t=" "+t;
        cnt=0;
        if(sam.match(fl,fr,1,0)){
            for(int j=cnt;j>=1;j--){
                cout<<(char)(ans[j]+'a');
            }
            cout<<'\n';
        }else cout<<-1<<'\n';
    }
    return 0;
}
