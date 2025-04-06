#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int MN=1e5+15;
stack<int> s;
int in[MN],out[MN],n,m,cnt,del[MN];
bool vis[2*MN];
vector<pair<int,int>> adj[MN];
// void dfs(int u){
//     for(int i=del[u];i<adj[u].size();i=del[u]){
//         del[u]=i+1;
//         dfs(adj[u][i]);
//     }
//     s.push(u);
// }
void dfs(int u){
    for(int i=del[u];i<adj[u].size();i=max(i+1,del[u])){
        int v=adj[u][i].first;
        if(!vis[adj[u][i].second]){
            vis[adj[u][i].second]=1;
            del[u]=i+1;
            dfs(v);
        }
    }
    s.push(u);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(make_pair(v,i));
        in[v]++;
        out[u]++;
    }
    bool flag=0;
    int start=0,end=0;
    for(int i=1;i<=n;i++){
        if(out[i]!=in[i]){
            flag=1;
            cnt++;
            if(out[i]-in[i]==1){
                start=i;
            }else if(out[i]-in[i]==-1){
                end=i;
            }else{
                cout<<"No";
                return 0;
            }
        }
    }
    if(cnt!=0&&cnt!=2){
        cout<<"No";
        return 0;
    }else{
        if(cnt==0) start=end=1;
        if(!start||!end){
            cout<<"No";
            return 0;
        }
        for(int i=1;i<=n;i++){
            sort(adj[i].begin(),adj[i].end());
        }
        dfs(start);
        while (!s.empty())
        {
            cout<<s.top()<<" ";
            s.pop();
        }
    }


    return 0;
}