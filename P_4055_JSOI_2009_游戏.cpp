#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e4+15;
int fx[4]={0,0,1,-1},fy[4]={1,-1,0,0};
int n,m,id[MN][MN],match[MN],dtot;
bool vis[MN];
vector<int> adj[MN],st;
vector<pir> ans;

bool dfs(int u){
    for(auto v:adj[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!match[v]||dfs(match[v])){
                match[u]=v;
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
} 

int solve(){
    int ret=0;
    for(auto p:st){
        if(!match[p]){
            memset(vis,0,sizeof(vis));
            if(dfs(p)) ret++;
        }
    }
    return ret;
}

void bfs(){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=dtot;i++){
        if(!match[i]) vis[i]=1,q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(match[v]){
                if(!vis[match[v]]) {
                    vis[match[v]]=1;
                    q.push(match[v]);
                }
            }
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char x;
            cin>>x;
            if(x=='.'){
                id[i][j]=++dtot;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!id[i][j]||!((i+j)&1)) continue;
            st.push_back(id[i][j]);
            for(int k=0;k<4;k++){
                int nx=i+fx[k],ny=j+fy[k];
                if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&id[nx][ny]){
                    adj[id[i][j]].push_back(id[nx][ny]);
                    adj[id[nx][ny]].push_back(id[i][j]);
                }
            }
        }
    }
    if((solve()<<1)==dtot){
        cout<<"LOSE\n";
    }else{
        cout<<"WIN\n";
        bfs();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[id[i][j]]){
                    cout<<i<<' '<<j<<'\n';
                }
            }
        }
    }
    return 0;
}