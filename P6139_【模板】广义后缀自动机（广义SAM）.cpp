#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=2e6+15;
int n;

struct gySAM{
    int nxt[MN][26],fa[MN],pos[MN],len[MN],cnt[MN],tot;
    int cnt_init[MN];
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++) adj[i].clear();
        tot=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
        cnt_init[0]=0;
    }

    gySAM(){
        init();
    }

    int newnode(int lst){
        int cur=++tot;
        cnt_init[cur]=1;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    int clone(int from){
        int cur=++tot;
        fa[cur]=fa[from];
        cnt_init[cur]=0;
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
            cnt[i]=-1;
        }
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    int dfs(int u){
        if(cnt[u]!=-1) return cnt[u];
        int sum=cnt_init[u];
        for(auto v:adj[u]){
            sum+=dfs(v);
        }
        cnt[u]=sum;
        return cnt[u];
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
    cin>>n;
    sam.init();
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        sam.insert(s);
    }
    ll ans=0;
    for(int i=1;i<=sam.tot;i++){
        ans+=sam.len[i]-sam.len[sam.fa[i]];
    }
    cout<<ans<<"\n"<<sam.tot+1;
    return 0;
}
