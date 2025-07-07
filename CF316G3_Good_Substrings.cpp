#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,L[MN],R[MN];
ll ans;
string s,t;

struct gySAM{
    int nxt[MN][26],fa[MN],pos[MN],len[MN],cnt[MN][12],tot;
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

    int newnode(int lst){
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
        int cur=newnode(lst);
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
            for(int i=0;i<=n;i++) cnt[u][i]+=cnt[v][i];
        }
        for(int i=1;i<=n;i++){
            if(cnt[u][i]<L[i]||cnt[u][i]>R[i]||!cnt[u][0]) return;
        }
        ans+=(len[u]-len[fa[u]]);
    }

    void insert(string s){
        int len=s.length();
        s=" "+s;
        pos[0]=0;
        for(int i=1;i<=len;i++){
            pos[i]=extend(s[i]-'a',pos[i-1]);
        }
    }

}sam;


int main(){
    cin>>s;
    sam.init();
    int lst=0;
    for(auto c:s){
        lst=sam.extend(c-'a',lst);
        sam.cnt[lst][0]++;
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>t>>L[i]>>R[i];
        lst=0;
        for(auto c:t){
            lst=sam.extend(c-'a',lst);
            sam.cnt[lst][i]++;
        }
    }
    sam.inittree();
    sam.dfs(0);
    cout<<ans;
    return 0;
}
