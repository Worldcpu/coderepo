#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int MN=2048;
int k,n,m,tot,ecc,dfn[MN],low[MN],color[MN],s[MN],top;
vector<int> adj[MN];
bool vis[MN];
void tarjan(int u){
    low[u]=dfn[u]=++tot;
    vis[u]=1;
    s[++top]=u;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        ecc++;
        int p;
        do
        {
            p=s[top--];
            color[p]=ecc;
            vis[p]=0;
        } while(p!=u);
        
    }
}
int main(){
    cin>>k;
    while (k--)
    {
        top=tot=ecc=0;
        cin>>n>>m;
        for(int i=1;i<MN;i++){
            dfn[i]=low[i]=color[i]=0;
            adj[i].clear();
        }
        char p1,p2;
        int a,b,xa,xb;
        //m->0 h->1
        for(int i=1;i<=m;i++){
            cin>>p1>>a>>p2>>b;
            int na=a+n,nb=b+n;
            if(p1=='m'&&p2=='h'){//a=0 b=1
                adj[b].push_back(a);//b=0 a=0
                adj[na].push_back(nb);//a=1 b=1
            }
            if(p1=='h'&&p2=='h'){//a=1 b=1
                adj[a].push_back(nb);
                adj[b].push_back(na);
            }
            if(p1=='h'&&p2=='m'){//a=1 b=0
                adj[a].push_back(b);
                adj[nb].push_back(na);
            }
            if(p1=='m'&&p2=='m'){// a=0 b=0
                adj[nb].push_back(a);
                adj[na].push_back(b);
            }
        }
        for(int i=1;i<=2*n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        bool flag=0;
        for(int i=1;i<=n;i++){
            if(color[i]==color[i+n]){
                cout<<"BAD"<<endl;
                flag=1;
                break;
            }
        }
        if(!flag) cout<<"GOOD"<<endl;
    }
    
    return 0;
}