#include<bits/stdc++.h>
using namespace std;
constexpr int MN=650;
int n,m,K;
string x,y;

struct ACAuto{
    int nxt[MN][26],fail[MN],end[MN],tot;

    void insert(string s,int st){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!nxt[p][k]) nxt[p][k]=++tot;
            p=nxt[p][k];
        }
        end[p]|=st;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(nxt[0][i]) q.push(nxt[0][i]);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                int v=nxt[u][i];
                if(v){
                    fail[v]=nxt[fail[u]][i];
                    q.push(v);
                }else nxt[u][i]=nxt[fail[u]][i];
            }
        }
    }

}ac;

struct Seq{
    vector<int> nxt[MN];

    int gnxt(int i,int c){
        auto ret=lower_bound(nxt[c].begin(),nxt[c].end(),i+1);\
        if(ret==nxt[c].end()) return 0;
        return *ret;
    }

}sq[2];


int main(){
    cin>>n>>m>>K;
    for(int i=1,qwq;i<=K;i++){
        cin>>qwq;
    }
    cin>>x>>y;
    x=" "+x,y=" "+y;
    for(int i=1;i<=n;i++){
        int k=x[i]-'a';
        sq[0].nxt[k].push_back(i);   
    }
    for(int i=1;i<=m;i++){
        int k=y[i]-'a';
        sq[1].nxt[k].push_back(i);   
    }
    for(int i=1;i<=K;i++){
        string qwq;
        cin>>qwq;
        ac.insert(qwq,1<<(i-1));
    }

    return 0;
}