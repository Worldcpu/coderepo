#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,ntot,id[MN][2];
string st[MN],ret[MN][2];
vector<int> adj[MN];

namespace Tarjan{
    int dfn[MN],low[MN],dtot,bel[MN],vtot,st[MN],top;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(low[u]==dfn[u]){
            vtot++;
            int p;
            do{
                p=st[top--];
                vis[p]=0;
                bel[p]=vtot;
            }while(p!=u);
        }
    }

    void solve(){
        for(int i=1;i<=ntot;i++){
            if(!dfn[i]) top=0,tarjan(i);
        }
        for(int i=1;i<=n;i++){
            if(bel[i<<1]==bel[i<<1|1]){
                cout<<"NO\n";
                return;
            }
        }
        cout<<"YES\n";
        for(int i=1;i<=n;i++){
            if(bel[i<<1]<bel[i<<1|1]) cout<<ret[i][0]<<'\n';   
            else cout<<ret[i][1]<<'\n';
        }
    }

}

namespace Trie{
    int nxt[MN][26],dtot=1,fa[MN],ep[MN][26];
    bool vis[MN];
    vector<int> pos[MN];

    void insert(string st,int id){
        int p=1;
        for(auto ch:st){
            int k=ch-'0';
            if(!nxt[p][k]) nxt[p][k]=++dtot;
            p=nxt[p][k];
        }
        pos[p].push_back(id);
    }

    void build(int u,int pre){
        int lst=ep[pre][0];
        for(auto p:pos[u]){
            id[p][0]=++ntot;
            adj[p].push_back(lst);
            adj[ntot].push_back(lst);
            adj[ntot].push_back(p^1);
            lst=ntot;
        }
        ep[u][0]=lst;
        lst=++ntot;
        if(nxt[u][0]) build(nxt[u][0],u),adj[lst].push_back(ep[nxt[u][0]][1]);
        if(nxt[u][1]) build(nxt[u][1],u),adj[lst].push_back(ep[nxt[u][1]][1]);
        reverse(pos[u].begin(),pos[u].end());
        for(auto p:pos[u]){
            id[p][1]=++ntot;
            adj[p].push_back(lst);
            adj[ntot].push_back(lst);
            adj[ntot].push_back(p^1);
            lst=ntot;
        }
        ep[u][1]=lst;
    }
}using namespace Trie;

int main(){
    cin>>n;
    ntot=n<<1|1;
    for(int i=1;i<=n;i++){
        cin>>st[i];
        bool flag=0;
        ret[i][0]=ret[i][1]=st[i];
        for(int j=0;j<st[i].length();j++){
            if(st[i][j]=='?'){
                ret[i][0][j]='0';
                ret[i][1][j]='1';
                flag=1;
            }
        }
        insert(ret[i][0],i<<1);
        insert(ret[i][1],i<<1|1);
        if(!flag){
            adj[i<<1].push_back(i<<1|1);
        }
    }
    build(1,0);
    Tarjan::solve();
    return 0;
}