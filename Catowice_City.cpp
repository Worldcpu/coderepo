#include<bits/stdc++.h>
using namespace std;
const int MN=1e6+15;
int T,n,m,cnt,top,s[MN],tot,siz[MN],col[MN],dfn[MN],low[MN];
vector<int> adj[MN];
bool vis[MN];
void read(int &x){
    x=0;
    int neg=0,ch=getchar();
    while (!(isdigit(ch)||ch=='-')&&ch!=EOF)
    {
        ch=getchar();
    }
    if(ch=='-'){
        neg=1;
        ch=getchar();
    }
    while (isdigit(ch))
    {
        x=x*10+(ch-'0');
        ch=getchar();
    }
    if(neg){
        x=-x;
    }
    // return neg?-res:res;
}
void tarjan(int u){
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
        cnt++;
        int p;
        do
        {
            p=s[top--];
            col[p]=cnt;
            vis[p]=0;
            siz[cnt]++;
        } while (p!=u);
        
    }
}
void clean(){
    top=cnt=tot=0;
    // memset(vis,0,sizeof(vis));
    // memset(siz,0,sizeof(siz));
    // memset(col,0,sizeof(col));
    // memset(dfn,0,sizeof(dfn));
    // memset(low,0,sizeof(low));
    for(int i=1;i<=n;i++){
        adj[i].clear();
        siz[i]=vis[i]=col[i]=dfn[i]=low[i]=0;
    }
}
void solve(){

    read(n);
    read(m);
    clean();
    for(int i=1;i<=m;i++){
        int u,v;
        read(u);
        read(v);
        if(u!=v) adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
    if(cnt==1){
        cout<<"No\n";
        return;
    }
    cout<<"Yes\n"<<siz[1]<<" "<<n-siz[1]<<"\n";
    for(int i=1;i<=n;i++){
        if(col[i]==1){
            cout<<i<<" ";
        }
    }
    cout<<"\n";
    for(int i=1;i<=n;i++){
        if(col[i]!=1){
            cout<<i<<" ";
        }
    }
    cout<<"\n";
}
int main(){
    cin>>T;
    while (T--)
    {
        solve();
    }
    
    return 0;
}