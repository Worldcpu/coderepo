#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int cf[MN],n,ans,k,maxx;
string s;

struct SAM{
    int nxt[MN][26],fa[MN],siz[MN],len[MN],cnt[MN],cnt_init[MN],tot,lst;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++) adj[i].clear();
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
        if(p==-1){
            fa[cur]=0;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
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
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

void getsiz(int u) {
    siz[u] = cnt_init[u]; // 初始大小为 cnt_init[u]
    for (auto v : adj[u]) {
        getsiz(v);
        siz[u] += siz[v];
    }
    if (siz[u] == k) {
        int l = (fa[u] == -1) ? 1 : len[fa[u]] + 1;
        int r = len[u];
        cf[l]++;
        cf[r + 1]--;
    }
}

}sam;

void init(){
    sam.init();
    memset(cf,0,sizeof(cf));
    maxx=ans=-1;
}

void solve(){
    init();
    cin>>s>>k;
    n=s.length();
    s=" "+s;
    for(int i=1;i<=n;i++){
        sam.extend(s[i]-'a');
    }
    sam.buildt();
    sam.getsiz(0);
    for(int i=1;i<=n;i++){
        cf[i]+=cf[i-1];
        if(cf[i]>=maxx){
            ans=i;
            maxx=cf[i];
        }
    }
    cout<<(maxx>0?ans:-1)<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
