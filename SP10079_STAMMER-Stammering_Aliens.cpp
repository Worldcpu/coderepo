#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,mxlen,p;
string s;

struct SAM{
    int nxt[MN][26],len[MN],fa[MN],cnt[MN],mxpos[MN],lst,tot;
    vector<int> adj[MN];

    int newnode(){
        int cur=++tot;
        len[cur]=fa[cur]=mxpos[cur]=cnt[cur]=0;
        adj[cur].clear();
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    int clone(int from){
        int cur=newnode();
        fa[cur]=fa[from];
        mxpos[cur]=mxpos[from];
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    void init(){
        lst=tot=0;
        lst=tot=newnode();
    }

    void expand(int c){
        int cur=newnode();
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
                int nq=clone(q);
                len[nq]=len[p]+1;
                fa[cur]=fa[q]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }

    void inittree(){
        for(int i=2;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            cnt[u]+=cnt[v];
            mxpos[u]=max(mxpos[u],mxpos[v]);
        }
        if(cnt[u]>=m){
            cerr<<"QWQ\n";
            if(mxlen<len[u]){
                mxlen=len[u];
                p=mxpos[u]-len[u];
            }else if(mxlen==len[u]){
                p=max(p,mxpos[u]-len[u]);
            }
        }
    }
}sam;

void init(){
    sam.init();
}

void solve(){
    init();
    cin>>s;
    n=s.length();
    s=" "+s;
    for(int i=1;i<=n;i++){
        sam.expand(s[i]-'a');
        sam.cnt[sam.lst]=1;
        sam.mxpos[sam.lst]=i;
    }
    sam.inittree();
    mxlen=-1,p=0;
    sam.dfs(1);
    if(mxlen){
        cout<<mxlen<<" "<<p<<'\n';
    }else cout<<"none\n";
}

int main(){
    while(1){
        cin>>m;
        if(m==0) break;
        solve();

    }

    return 0;
}
