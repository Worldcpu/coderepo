#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int in[MN],n,ret,a[MN],b[MN];
map<int,bool> mp;
vector<int> adj[MN];

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(a[i]==0&&b[i]==0){
            q.push(i);
            mp[i]=1;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(!mp[v]){
                mp[v]=1;
                q.push(v);
            }
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        adj[a[i]].push_back(i);
        adj[b[i]].push_back(i);
    }
    toposort();
    cout<<mp.size();

    return 0;
}