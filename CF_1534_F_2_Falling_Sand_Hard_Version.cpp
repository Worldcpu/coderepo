#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15,INF=1e9;
int a[MN],ans,n,m,stot,dg[MN],in[MN],val[MN],p[MN],qjtot;
pir qj[MN];
bool sel[MN];
vector<int> adj[MN],G[MN];
vector<int> sd[MN];

namespace Tarjan{
    int col[MN],low[MN],dfn[MN],dtot,st[MN],top,ctot;
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
        if(dfn[u]==low[u]){
            ctot++;
            int x;
            do{
                x=st[top--];
                col[x]=ctot;  
                vis[x]=0;      
            }while(x!=u);
        }
    }

}using namespace Tarjan;

int getpos(int x,int y){
    return (x-1)*m+y;
}

void toposort(){
    queue<int> q;
    vector<int> tmp;
    for(int i=1;i<=ctot;i++){
        if(!dg[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(sel[u]) in[u]=1;
        tmp.push_back(u);
        for(auto v:G[u]){
            dg[v]--;
            if(!dg[v]) q.push(v);
            if(in[u]) in[v]=1,sel[v]=0;
        }
    }
    for(int i=1;i<=ctot;i++){
        qj[i]=pir(INF,-INF);   
    }
    for(int i=1;i<=m;i++){
        if(sel[p[i]]&&qj[p[i]].first==INF){ 
            ++qjtot;
            qj[p[i]]=pir(qjtot,qjtot);
        }
    }
    for(int i=tmp.size()-1;i>=0;i--){
        int u=tmp[i];
        for(auto v:G[u]){
            qj[u].first=min(qj[u].first,qj[v].first);
            qj[u].second=max(qj[u].second,qj[v].second);
        }
    }
    sort(qj+1,qj+1+ctot);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='#'){
                sd[j].push_back(i);
                a[getpos(i,j)]=++stot;
            }
        }
    }
    for(int i=1;i<=m;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<sd[i].size();j++){
            int u=a[getpos(sd[i][j],i)];
            if(j&&sd[i][j-1]+1==sd[i][j]){
                adj[u].push_back(a[getpos(sd[i][j-1],i)]);
            }
            if(j+1<sd[i].size()){
                adj[u].push_back(a[getpos(sd[i][j+1],i)]);
            }
            if(i>1){
                auto it=lower_bound(sd[i-1].begin(),sd[i-1].end(),sd[i][j]);
                if(it!=sd[i-1].end()) adj[u].push_back(a[getpos(*it,i-1)]);
            }
            if(i<m){
                auto it=lower_bound(sd[i+1].begin(),sd[i+1].end(),sd[i][j]);
                if(it!=sd[i+1].end()) adj[u].push_back(a[getpos(*it,i+1)]);
            }
        }
    }
    for(int i=1;i<=stot;i++){
        if(!Tarjan::dfn[i]){
            Tarjan::tarjan(i);
        }
    }
    for(int i=1;i<=m;i++){
        int d=sd[i].size()-val[i];
        if(d>=0&&d<sd[i].size()){
            p[i]=col[a[getpos(sd[i][d],i)]];           
            sel[p[i]]=1;
        }
    }
    for(int i=1;i<=stot;i++){
        for(auto v:adj[i]){
            if(col[i]!=col[v]){
                G[col[i]].push_back(col[v]);               
                dg[col[v]]++;
            }
        }
    }
    toposort();
    for(int i=1,now=0,r=0;i<=ctot&&now<qjtot;i++){
        r=max(r,qj[i].second);
        if(i==ctot||qj[i+1].first>now+1){
            ans++;
            now=r;
        }
    }
    cout<<ans;
    return 0;
}
