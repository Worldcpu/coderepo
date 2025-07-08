#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=3e6+15;
int n,m,q;
bool vis[MN];
string s,t;

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],ed[MN],tot,lst;
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
        ed[cur]++;
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
            ed[u]+=ed[v];
        }
    }

}sam;

int main(){
    cin>>s;
    sam.init();
    n=s.length();
    s=' '+s;
    for(int i=1;i<=n;i++){
        sam.extend(s[i]-'a');
    }
    sam.inittree();
    sam.dfs(0);
    cin>>q;
    while(q--){
        cin>>t;
        m=t.length();
        t=" "+t;
        vector<int> del;
        int p=0,lcs=0,ans=0;
        for(int i=1;i<m*2;i++){
            int k=t[i>m?i-m:i]-'a';
            while(p!=-1&&!sam.nxt[p][k]) p=sam.fa[p],lcs=sam.len[p];
            if(p==-1){
                p=0;
            }else{
                p=sam.nxt[p][k];
                lcs++;
                while(lcs>m){
                    if((--lcs)<=sam.len[sam.fa[p]]) p=sam.fa[p];
                }
                if(lcs>=m&&!vis[p]){
                    ans+=sam.ed[p];
                    vis[p]=1;
                    del.push_back(p);
                }
            }
        }
        cout<<ans<<'\n';
        for(auto it:del){
            vis[it]=0;
        }
    }
    return 0;
}
