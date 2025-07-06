#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=3e6+15;
int n;
ll ans;
string s;

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],cnt[MN],tot,lst;
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
        if(cnt[u]!=1){
            ans=max(ans,1ll*cnt[u]*len[u]);
        }
        return cnt[u];
    }

}sam;

int main(){
    cin>>s;
    n=s.length();
    s=" "+s;
    sam.init();
    for(int i=1;i<=n;i++){
        sam.extend(s[i]-'a');
    }
    sam.inittree();
    sam.dfs(0);
    cout<<ans;
    return 0;
}
