#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e6+15;
string a,b;

struct gySAM{
    int nxt[MN][26],fa[MN],pos[MN],len[MN],cnt1[MN],cnt2[MN],tot;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++) adj[i].clear();
        tot=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
    }

    int extend(int c,int lst){
        if(nxt[lst][c]&&len[nxt[lst][c]]==len[lst]+1) return nxt[lst][c];
        int cur=++tot;
        len[cur]=len[lst]+1;
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
        for(int i=1;i<=tot;i++) adj[fa[i]].push_back(i);
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            cnt1[u]+=cnt1[v];
            cnt2[u]+=cnt2[v];
        }
    }

    void insert(string s,int *cnt){
        int len=s.length();
        s=" "+s;
        pos[0]=0;
        for(int i=1;i<=len;i++){
            pos[i]=extend(s[i]-'a',pos[i-1]);
            cnt[pos[i]]++;
        }
    }

}sam;

int main(){
    cin>>a>>b;
    sam.init();
    sam.insert(a,sam.cnt1);
    sam.insert(b,sam.cnt2);
    sam.inittree();
    sam.dfs(0);
    ll ans=1e9;
    for(int i=1;i<=sam.tot;i++){
        if(sam.cnt1[i]==sam.cnt2[i]&&sam.cnt1[i]==1){
            ans=min(ans,1ll*sam.len[sam.fa[i]]+1);
        }
    }
    cout<<(ans==1e9?-1:ans);
    return 0;
}
