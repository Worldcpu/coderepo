#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e4+15;
int n;
bool vis[MN],inst[MN];

namespace ACAuto{
    struct Node{
        int ch[2];
        int end,fail;
    }t[MN];
    int tot;

    void insert(string s){
        int p=0;
        for(auto c:s){
            int cp=c-48;
            if(!t[p].ch[cp]) t[p].ch[cp]=++tot;
            p=t[p].ch[cp];
        }
        t[p].end=1;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<=1;i++){
            if(t[0].ch[i]) q.push(t[0].ch[i]);
        }
        while(!q.empty()){
            int f=q.front();
            q.pop();
            for(int i=0;i<=1;i++){
                int v=t[f].ch[i];
                if(v){
                    t[v].fail=t[t[f].fail].ch[i];
                    t[v].end|=t[t[t[f].fail].ch[i]].end;
                    q.push(v);
                }else t[f].ch[i]=t[t[f].fail].ch[i];
            }
        }
    }

}using namespace ACAuto;

void dfs(int u){
    if(inst[u]){
        cout<<"TAK";
        exit(0);
    }
    if(vis[u]||t[u].end) return;
    inst[u]=vis[u]=1;
    dfs(t[u].ch[0]);
    dfs(t[u].ch[1]);
    inst[u]=0;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string st;
        cin>>st;
        insert(st);
    }
    build();
    dfs(0);
    cout<<"NIE";
    return 0;
}
