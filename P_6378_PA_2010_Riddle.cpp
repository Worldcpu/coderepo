// 注释：DeepseekR1 and V3,WJY
// 可以线段树优化，但是问题是你要开好多个线段树来存储[1,x-1],[x,n]的节点信息，空间很炸裂，但也能做
#include<bits/stdc++.h>
using namespace std;
const int MN=8e6+15;
int n,m,k,dfn[MN],low[MN],vdcc[MN],tot,dcc; 
// dfn: DFS序, low: Tarjan算法中的low值, 
// vdcc: 强连通分量编号, tot: dfn时间戳, dcc: 强连通分量计数器
vector<int> adj[MN],gp[MN]; //gp: 存储每个部分(题意中的部分)的点
bool vis[MN];
int s[MN],top;

void tarjan(int u){
    // tarjan求强联通
    low[u]=dfn[u]=++tot;
    s[++top]=u;
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
        dcc++;
        int p;
        do
        {
            p=s[top--];
            vdcc[p]=dcc;
            vis[p]=0;
        } while (p!=u);
    }
}

// 以下注释中
// ¬u表示u的否定，即u+n
// u的前缀辅助点，即u+2n
// u的后缀辅助点，即u+3n
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        int fu=u+n,fv=v+n;
        adj[fu].push_back(v); // 添加边¬u → v
        adj[fv].push_back(u); // 添加边¬v → u
    }
    for(int i=1;i<=k;i++){
        int num;
        cin>>num;
        for(int j=1;j<=num;j++){
            int p;
            cin>>p;
            gp[i].push_back(p);
            adj[p].push_back(p+2*n); // 添加边 p → p+2n（前缀变量）
            adj[p+3*n].push_back(p+n); // 添加边 p+3n → ¬p（后缀变量）
        }
        for(int j=1;j<gp[i].size();j++){
            int d1=gp[i][j-1],d2=gp[i][j]; // 前一个点和当前点

            adj[d1+2*n].push_back(d2+2*n); // 添加边 d1+2n → d2+2n（前缀传递）
            adj[d2+3*n].push_back(d1+3*n); // 添加边 d2+3n → d1+3n（后缀传递，可以看图理解）

            adj[d1+2*n].push_back(d2+n); // 添加边 d1+2n → ¬d2（前缀已选，d2不可选）
            adj[d2].push_back(d1+3*n); // 添加边 d2 → d1+3n（选d2，后缀必须选到d1）
        }
    }


    for(int i=1;i<=n*4;i++){
        if(!dfn[i]) tarjan(i);
    }

    for(int i=1;i<=n;i++){
        if(vdcc[i]==vdcc[i+n] || vdcc[i+2*n]==vdcc[i+3*n]){ 
            // 如果i和¬i在同一分量，或前缀和后缀变量在同一分量则环无解
            cout<<"NIE";
            return 0;
        }
    }
    cout<<"TAK";
    return 0;
}
