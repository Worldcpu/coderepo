#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e6+15;
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

    int extend(int c,int lst){
        if(nxt[lst][c]&&len[nxt[lst][c]]==len[lst]+1) return nxt[lst][c];
        int cur=++tot;
        len[cur]=len[lst]+1;
        cnt_init[cur]=1;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        int p=lst;
        while(p!=-1&&!nxt[p][c]){
            nxt[p][c]=cur;
            p=fa[p];
        }
        bool flag=0;
        if(p==-1) fa[cur]=0;
        else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
                return cur;
            }
            else{
                if(p==lst) flag=1,cur=MN-1,tot--;
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
                return flag?nq:cur;
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
