#include<iostream>
#include<vector>
using namespace std;
const int MN=1145;
int tot,low[MN],dfn[MN],ecc,color[MN],n,s[MN],top,in[MN],out[MN];
bool vis[MN];
vector<int> adj[MN],sdt[MN];
void tarjan(int u){
    low[u]=dfn[u]=++tot;
    vis[u]=1;
    s[++top]=u;
    for(auto v : adj[u]){
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
            vis[p]=0;
            color[p]=ecc;

        } while (p!=u);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int v;
        while (1)
        {
            cin>>v;
            if(v==0){
                break;
            }
            adj[i].push_back(v);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto v : adj[i]){
            int ci=color[i],cv=color[v];
            if(ci!=cv){
                in[cv]++;
                out[ci]++;
            }
        }
    }
    int ansi=0,anso=0;
    for(int i=1;i<=ecc;i++){
        if(!in[i]){
            ansi++;
        }
        if(!out[i]){
            anso++;
        }
    }
    if(ecc==1){
        cout<<"1\n0";
    }
    else cout<<ansi<<endl<<max(ansi,anso);
    return 0;
}