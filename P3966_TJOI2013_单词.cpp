#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int n,s[MN],top;

struct ACAuto{
    int t[MN][26],tot,cnt[MN],end[MN],fail[MN];

    void insert(string s,int id){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
            cnt[p]++;
        }
        end[id]=p;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(t[0][i]){
                q.push(t[0][i]);
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            s[++top]=u;
            for(int i=0;i<26;i++){
                int v=t[u][i];
                if(v){
                    fail[v]=t[fail[u]][i];
                    q.push(v);
                }else t[u][i]=t[fail[u]][i];
            }
        }
    }


}t;


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        t.insert(s,i);
    }
    t.build();
    for(int i=top;i>=0;i--){
        t.cnt[t.fail[s[i]]]+=t.cnt[s[i]];
    }
    for(int i=1;i<=n;i++){
        cout<<t.cnt[t.end[i]]<<'\n';
    }

    return 0;
}
