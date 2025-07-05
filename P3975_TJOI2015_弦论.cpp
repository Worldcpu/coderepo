#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int t,k,n,f[MN];
string s;

struct SAM{
    int nxt[MN][26],len[MN],fa[MN],cnt[MN],cnt_init[MN],tot,lst;
    bool vis[MN];
    vector<int> adj[MN];

    void init(){
        tot=lst=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
        cnt_init[0]=0;
    }

    void extend(int c){
        int cur=++tot;
        len[cur]=len[lst]+1;
        cnt_init[cur]=1;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        int p=lst;
        while(p!=-1&&!nxt[p][c]){
            nxt[p][c]=cur;
            p=fa[p];
        }
        if(p==-1) fa[cur]=0;
        else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }
            else{
                int nq=++tot;
                len[nq]=len[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[nq]=fa[q];
                cnt_init[nq]=0;
                while(p!=-1&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
                fa[q]=fa[cur]=nq;
            }
        }
        lst=cur;
    }

    void buildt(){
        for(int i=0;i<=tot;i++){
            cnt[i]=-1;
            adj[i].clear();
        }
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }
    
    int dfs(int u){
        if(cnt[u]!=-1) return cnt[u];
        int sum=cnt_init[u];
        for(auto v:adj[u]){
            dfs(v);
            sum+=cnt[v];
        }
        return cnt[u]=sum;
    }

    void getf1(int u){
        f[u]=cnt[u];
        for(auto v:adj[u]){
            getf1(v);
        }
    }

    int getf2(int u){
        if(vis[u]) return f[u];
        vis[u]=1;
        for(int i=0;i<26;i++){
            int v=nxt[u][i];
            if(v) f[u]+=getf2(v);
        }
        return f[u];
    }

    void getf(int op){
        if(!op){
            for(int i=1;i<=tot;i++) f[i]=cnt[i]=1;
        }else dfs(0),getf1(0);
        f[0]=cnt[0]=0;
        getf2(0);
    }

    void query(int u,int k){
        if(k>f[u]){
            cout<<-1;
            return;
        }
        if(k<=cnt[u]) return;
        k-=cnt[u];
        for(int i=0;i<26;i++){
            int v=nxt[u][i];
            if(v && k>f[v]) k-=f[v];
            else if(v){
                cout<<(char)(i+'a');
                query(v,k);
                return;
            }
        }
    }

}sam;


signed main(){
    cin>>s>>t>>k;
    n=s.length();
    s=" "+s;
    sam.init();
    for(int i=1;i<=n;i++){
        sam.extend(s[i]-'a');
    }
    sam.buildt();
    sam.getf(t);
    sam.query(0,k);
    return 0;
}
