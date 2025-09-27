#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Line{
    int x1,y1,x2,y2,tg;
}ln[MN];
int n,ans;
vector<int> adj[MN];

namespace Hungry{
    int p[MN];
    bool vis[MN];

    bool dfs(int u){
        if(vis[u]) return 0;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!vis[v]){
                vis[v]=1;
                if(!p[v]||dfs(p[v])){
                    p[v]=u;
                    return 1;
                }
            }
        }
        return 0;
    }
}using namespace Hungry;

bool check(int i,int j){
    if(ln[i].x1>=ln[j].x1&&ln[i].x1<=ln[j].x2){
        if(ln[j].y1>=ln[i].y1&&ln[j].y1<=ln[i].y2) return 1;
    }
    return 0;
}

bool cmp(Line x,Line y){
    return x.tg<y.tg;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>ln[i].x1>>ln[i].y1>>ln[i].x2>>ln[i].y2;
        if(ln[i].x1==ln[i].x2){
            ln[i].tg=1;
            if(ln[i].y1>ln[i].y2){
                swap(ln[i].y1,ln[i].y2);
            }
        }
        if(ln[i].y1==ln[i].y2){
            ln[i].tg=2;
            if(ln[i].x1>ln[i].x2){
                swap(ln[i].x1,ln[i].x2);
            }
        }
    }
    sort(ln+1,ln+1+n,cmp);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(check(i,j)){
                adj[i].push_back(j);
            }
        }
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans+=dfs(i);
    }
    cout<<n-ans;

    return 0;
}