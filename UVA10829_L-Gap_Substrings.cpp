#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,g,casetot;
string s;

struct SAM{
    int nxt[MN][26],len[MN],pos[MN],fa[MN],tot,lst;
    int siz[MN],dep[MN],hson[MN],htop[MN];
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
            len[i]=fa[i]=0;
            siz[i]=dep[i]=hson[i]=htop[i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        tot=lst=1;
    }

    void expand(int c,int id){
        int cur=++tot;
        len[cur]=len[lst]+1;
        pos[id]=cur;
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
                len[nq]=len[p]+1;
                fa[nq]=fa[q];
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[cur]=fa[q]=nq;
                while(p&&nxt[p][c]==q) nxt[p][c]=nq,p=fa[p];
            }
        }
        lst=cur;
    }

    void dfs1(int u,int pre){
        siz[u]=1;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            dfs1(v,u);
            siz[u]+=siz[v];
            if(!hson[u]||siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    void inittree(){
        for(int i=2;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
        dfs1(1,0);
        dfs2(1,1);
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

    int lcs(int x,int y){
        x=pos[x],y=pos[y];
        return len[lca(x,y)];
    }

}sam1,sam2;

void solve(){
    sam1.init();
    sam2.init();
    cin>>g>>s;
    n=s.length();
    s=" "+s;
    for(int i=1;i<=n;i++){
        sam1.expand(s[i]-'a',i);
    }
    for(int i=n;i>=1;i--){
        sam2.expand(s[i]-'a',i);
    }
    sam1.inittree();
    sam2.inittree();
    int ans=0;
    for(int j=1;j<=(n-g)>>1;j++){
        for(int i=1;i+j+g<=n;i+=j){
            int l=i,r=i+j+g;
            int lcs=min(sam1.lcs(l,r),j),lcp=min(sam2.lcs(l,r),j);
            int len=lcs+lcp-1;
            if(len>=j) ans+=len-j+1;
        }
    }
    cout<<"Case "<<++casetot<<": "<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
