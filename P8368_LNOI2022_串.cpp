#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e6+15;
int n;
ll ans;
string s;

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],cnt[MN],pos[MN],mnpos[MN],tot,lst;
    vector<int> adj[MN];


    int newnode(){
        int cur=++tot;
        mnpos[cur]=1e9;
        fa[cur]=len[cur]=cnt[cur]=0;
        adj[cur].clear();
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    void init(){
        tot=lst=0;
        tot=lst=newnode();
    }

    int clone(int from){
        int cur=newnode();
        fa[cur]=fa[from];
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
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
                fa[q]=fa[cur]=nq;
                while(p&&nxt[p][c]==q) nxt[p][c]=nq,p=fa[p];
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
            mnpos[u]=min(mnpos[u],mnpos[v]);
        }
        if(cnt[u]>=2){
            ans=max(ans,1ll*len[u]+(n-mnpos[u])/2);
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
        sam.cnt[sam.lst]++;
        sam.mnpos[sam.lst]=i;
    }
    sam.inittree();
    ans=n/2;
    sam.dfs(1);
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
