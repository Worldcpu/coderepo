#include<iostream>
#include<vector>
using namespace std;
const int MN=5e5+15,MM=2e6+16;
int n,m,dfn[MN],root,vdcc,cnt,low[MN];
vector<int> adj[MN],ans[MN];
int s[MN],top;
void tarjan(int u,int fa){
    low[u]=dfn[u]=++cnt;
    s[++top]=u;
    if(adj[u].empty()&&u==fa){
        ans[++vdcc].push_back(u);
        return;
    }
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                vdcc++;
                int p;
                do
                {
                    p=s[top--];
                    ans[vdcc].push_back(p);
                } while (p!=v);
                ans[vdcc].push_back(u);
            }
        }else low[u]=min(low[u],dfn[v]);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(u==v) continue;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,i);
        }
    }
    cout<<vdcc<<endl;
    for(int i=1;i<=vdcc;i++){
        cout<<ans[i].size()<<" ";
        for(int j=0;j<ans[i].size();j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}