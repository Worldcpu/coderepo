#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e6+15;
int n,c,a[MN],dg[MN],tmp[MN],cntt;
ll ans=0;
vector<int> adj[MN];

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

    void insert(int cntt){
        pos[0]=0;
        for(int i=1;i<=cntt;i++){
            pos[i]=extend(tmp[i],pos[i-1]);
        }
    }

}sam;

void dfs(int u,int pre,int lst){
    int lstt=sam.extend(a[u],lst);
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u,lstt);
    }
}

int main(){
    sam.init();
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        dg[u]++;
        dg[v]++;
    }
    for(int i=1;i<=n;i++){
        if(dg[i]==1){
            dfs(i,0,0);
            cntt=0;
        }
    }
    for(int i=1;i<=sam.tot;i++){
        ans+=sam.len[i]-sam.len[sam.fa[i]];
    }
    cout<<ans;
    return 0;
}
