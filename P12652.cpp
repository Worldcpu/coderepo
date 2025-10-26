#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN];
vector<int> adj[MN];
priority_queue<pir,vector<pir>,greater<pir>> q;

int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        adj[x].push_back(i);
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    q.push(pir(a[1],1));
    while(!q.empty()){
        auto tp=q.top();
        q.pop();
        cout<<tp.first<<'\n';
        for(auto v:adj[tp.second]){
            q.push(pir(a[v],v));
        }
    }


    return 0;
}