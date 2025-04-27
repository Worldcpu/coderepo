#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15;
struct Node{
    int x,y;
}nd[MN];
int n,maxx;
map<pir,int> um;
map<pir,bool> vis;
set<int,greater<int>> s[MN];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>nd[i].x>>nd[i].y;
        um[pir(nd[i].x,nd[i].y)]=i;
        s[nd[i].x].insert(nd[i].y);
        maxx=max(maxx,nd[i].x);
    }
    int ans=n;
    for(int i=1;i<maxx;i++){
        for(auto p:s[i]){
            if(um[pir(i+1,p+1)]&&!vis[pir(i+1,p+1)]){
                ans--;
                vis[pir(i+1,p+1)]=1;
            }
            else if(um[pir(i+1,p)]&&!vis[pir(i+1,p)]){
                ans--;
                vis[pir(i+1,p)]=1;
            }
            else if(um[pir(i+1,p-1)]&&!vis[pir(i+1,p-1)]){
                ans--;
                vis[pir(i+1,p-1)]=1;
            }
        }
    }
    cout<<ans;
    return 0;
}