#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15,MP=5125;
int n,m,k,in[MN],f[MP][MP];
struct edge{
    int v,w;
};
vector<edge> adj[MN],fadj[MN];
vector<int> ans;

void getans(int cnt){
    int u=n;
    ans.push_back(u);
    while (u!=1)
    {
        for(auto e:fadj[u]){
            int v=e.v,w=e.w;
            if(f[u][cnt]==f[v][cnt-1]+w){
                ans.push_back(v);
                u=v;
                cnt--;
                break;
            }
        }
    }
    
}

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!in[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            for(int i=1;i<n;i++){
                f[v][i]=min(f[v][i],f[u][i-1]+w);
            }
            in[v]--;
            if(!in[v]){
                q.push(v);
            }
        }        
    }
}

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        fadj[v].push_back({u,w});
        in[v]++;
    }
    memset(f,0x3f,sizeof(f));
    f[1][0]=0;
    toposort();
    for(int i=n;i>=1;i--){
        if(f[n][i]<=k){
            cout<<i+1<<'\n';
            getans(i);
            for(int j=ans.size()-1;j>=0;j--){
                cout<<ans[j]<<" ";
            }
            break;
        }
    }
    return 0;
}