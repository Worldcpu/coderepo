#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,L[MN],R[MN],in[MN],res[MN],tot;
vector<int> adj[MN];

void toposort(){
    priority_queue<int> q;
    for(int i=1;i<=n;i++){
        if(!in[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.top();
        q.pop();
        res[u]=++tot;
        for(auto v:adj[u]){
            if(!(--in[v])){
                q.push(v);
            }
        }
    }
}

void init(){
    for(int i=1;i<=n;i++) adj[i].clear();
    tot=0;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        for(int j=1;j<i;j++){
            if(L[i]<=L[j]&&R[j]<=R[i]){
                adj[i].push_back(j);
                in[j]++;
            }
            if(L[j]<=L[i]&&R[i]<=R[j]){
                adj[j].push_back(i);
                in[i]++;
            }
        }
    }
    toposort();
    for(int i=1;i<=n;i++){
        cout<<n-res[i]+1<<' ';
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
}