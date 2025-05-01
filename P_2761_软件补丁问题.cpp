#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
constexpr int MN=520,MM=(1<<22)+15;
int n,m,S,w[MN],dis[MM],f1[MN],f2[MN],b1[MN],b2[MN];
bool vis[MM];

bool isok(int i,int id){
    if((i|b1[id])!=i){
        return 0;
    }
    if((i&b2[id])) return 0;
    return 1;
}

void spfa(){
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    q.push(S);
    dis[S]=0;
    vis[S]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=1;i<=m;i++){
            if(!isok(u,i)) continue;
            int v=u^(u&f1[i]);
            v|=f2[i];
            if(dis[v]>dis[u]+w[i]){
                dis[v]=dis[u]+w[i];
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
}

signed main(){
    cin>>n>>m;
    S=(1<<(n))-1;
    for(int i=1;i<=m;i++){
        string a,b;
        cin>>w[i]>>a>>b;
        for(int j=0;j<n;j++){
            char p=a[j];
            if(p=='+'){
                b1[i]+=(1<<j);
            }else if(p=='-'){
                b2[i]+=(1<<j);
            }
        }
        for(int j=0;j<n;j++){
            char p=b[j];
            if(p=='+'){
                f2[i]+=(1<<j);
            }else if(p=='-'){
                f1[i]+=(1<<j);
            }
        }
    }
    spfa();
    if(dis[0]>=0x3f3f3f3f3f3f3f3f){
        cout<<0;
    }else cout<<dis[0];
    return 0;
}