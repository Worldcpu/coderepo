#include<iostream>
#include<vector>
#include<stack>
#include<cstring>
#include<unordered_map>
#include<algorithm>
using namespace std;
const int MN=1e4+15,ME=1e5+15;
vector<int> e[ME],ans[MN];
int dfn[MN],low[MN],color[MN];
bool vis[MN];
stack<int> s;
int n,m,cnt=0,tot=0;
void tarjan(int u){
    dfn[u]=low[u]=++cnt;
    s.push(u);
    vis[u]=1;
    for(int i=0;i<e[u].size();i++){
        int v=e[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        tot++;
        int pre;
        do{
            pre=s.top();
            s.pop();
            color[pre]=tot;
            vis[pre]=0;
            // ans[tot].push_back(pre);
        }while (pre!=u);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    cout<<tot<<endl;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++){
        ans[color[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if(!vis[color[i]]){
            vis[color[i]]=1;
            for(int j=0;j<ans[color[i]].size();j++){
                cout<<ans[color[i]][j]<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}