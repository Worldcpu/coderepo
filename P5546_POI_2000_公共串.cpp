#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5200;
int n,minn,mn[MN],mnid;
string s[MN];

struct SAM{
    int nxt[MN][26],mx[MN],fa[MN],len[MN],cnt[MN],tot,lst;
    int cnt_init[MN];
    vector<int> adj[MN];

    void init(){
        tot=0;
        lst=0;
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

    void inittree(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
            cnt[i]=-1;
            mn[i]=len[i];
        }
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            mx[u]=max(mx[u],mx[v]);
        }
        mn[u]=min(mn[u],mx[u]);
    }

    void match(string s){
        int slen=s.length();
        s=" "+s;
        for(int i=0;i<=tot;i++) mx[i]=0;
        int p=0,lcs=0;
        for(int i=1;i<=slen;i++){
            int k=s[i]-'a';
            if(nxt[p][k]){
                p=nxt[p][k];
                lcs++;
                mx[p]=max(mx[p],lcs);
            }else{
                while(p!=-1&&!nxt[p][k]) p=fa[p];
                if(p==-1){
                    p=lcs=0;
                }else{
                    lcs=len[p]+1;
                    p=nxt[p][k];
                    mx[p]=max(mx[p],lcs);
                }
            }
        }
        dfs(0);
    }

}sam;

int main(){
    cin>>n;
    minn=1e9;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        if(s[i].length()<minn){
            minn=s[i].length(),mnid=i;
        }
    }
    if(n==1){
        cout<<minn;
        return 0;
    }
    sam.init();
    for(auto c:s[mnid]){
        sam.extend(c-'a');
    }
    sam.inittree();
    for(int i=1;i<=n;i++){
        if(i!=mnid){
            sam.match(s[i]);
        }
    }
    int ans=0;
    for(int i=0;i<=sam.tot;i++) ans=max(ans,mn[i]);
    cout<<ans;
    return 0;
}
