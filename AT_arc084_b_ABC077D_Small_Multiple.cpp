#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
struct Node{
    int u,w;
};
int K;
bool vis[MN];

void bfs(){
    deque<Node> q;
    q.push_back({1,1});
    vis[1]=1;
    while(!q.empty()){
        Node f=q.front();
        q.pop_front();
        if(f.u==0){
            cout<<f.w<<'\n';
            return;
        }
        if(!vis[10*f.u%K]){
            q.push_front({10*f.u%K,f.w});
            vis[10*f.u%K]=1;
        }
        if(!vis[f.u+1]){
            q.push_back({f.u+1,f.w+1});
        }
    }
}


int main(){
    cin>>K;
    bfs();
    return 0;
}
