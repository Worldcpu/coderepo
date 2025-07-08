#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+114;
int n,ans,pre[MN],p[MN],id[MN];
vector<int> col[MN];

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],tot;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
            fa[i]=len[i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        tot=1;
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

    int extend(int c,int lst){
        if(nxt[lst][c]&&len[nxt[lst][c]]==len[lst]+1) return nxt[lst][c];
        int cur=newnode(),p=lst,flag=0,q,nq;
        len[cur]=len[p]+1;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                if(p==lst) flag=1,cur=0,tot--;
                nq=clone(q);
                len[nq]=len[p]+1;
                fa[q]=fa[cur]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        return flag?nq:cur;
    }

    void inittree(){
        for(int i=2;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    void insert(string s,int color){
        int lst=1;
        for(char c:s){
            lst=extend(c-'a',lst);
            col[lst].push_back(color);
        }
    }

    void dfs(int u){
        p[u]=u;
        for(int v:adj[u]) dfs(v);
    }
}sam;

bool cmp(int x,int y){
    return sam.len[x]>sam.len[y];
}

void initpre(){
    for(int i=0;i<MN;i++) pre[i]=i;
}

int root(int x){
    return pre[x]==x?x:pre[x]=root(pre[x]);
}

void solve(){
    sort(p+1,p+1+sam.tot,cmp);
    for(int i=1;i<=sam.tot;i++){
        int u=p[i];
        id[u]=0;
        if(!col[u].empty()){
            id[u]=root(col[u][0]);
            for(int j=1;j<col[u].size();j++){
                int v=root(col[u][j]);
                if(v!=id[u]){
                    ans+=sam.len[u];
                    pre[v]=id[u];
                }
            }
        }
        for(int v:sam.adj[u]){
            int rv=root(id[v]);
            if(!rv) continue;
            if(!id[u]) id[u]=rv;
            else if(rv!=id[u]){
                ans+=sam.len[u];
                pre[rv]=id[u];
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    initpre();
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        sam.insert(s,i);
    }
    sam.inittree();
    sam.dfs(1);
    solve();
    cout<<ans;
    return 0;
}
