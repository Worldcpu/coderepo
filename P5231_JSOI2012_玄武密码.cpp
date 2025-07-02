#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m;
string s,tst[MN];

struct ACAuto{
    int t[MN][26],tot,end[MN],fail[MN];
    bool vis[MN];

    void insert(string s){
        int p=0;
        for(auto c:s){
            int k=c-'A';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[p]++;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(t[0][i]) q.push(t[0][i]);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                int v=t[u][i];
                if(v){
                    fail[v]=t[fail[u]][i];
                    q.push(v);
                }else t[u][i]=t[fail[u]][i];
            }
        }
    }

    void prework(string s){
        int p=0;
        for(auto c:s){
            int k=c-'A';
            p=t[p][k];
            for(int i=p;i&&!vis[i];i=fail[i]){
                vis[i]=1;
            }
        }
    }

    int query(string s){
        int p=0,ret=0;
        for(int i=0;i<s.length();i++){
            int k=s[i]-'A';
            p=t[p][k];
            if(vis[p]) ret=i+1;
        }
        return ret;
    }

}t;


int main(){
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++){
        cin>>tst[i];
        t.insert(tst[i]);
    }
    t.build();
    t.prework(s);
    for(int i=1;i<=m;i++){
        cout<<t.query(tst[i])<<'\n';
    }
    return 0;
}
