#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,top;
int s1[MN];
char s2[MN];
string s;

namespace ACAuto{
    int tot,trie[MN][26];
    int end[MN],fail[MN];

    void insert(string s){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!trie[p][k]) trie[p][k]=++tot;
            p=trie[p][k];
        }
        end[p]=s.length();
    }

    void build(){
        queue<int> q;
        memset(fail,0,sizeof(fail));
        for(int i=0;i<26;i++){
            if(trie[0][i]) q.push(trie[0][i]);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                if(trie[u][i]){
                    fail[trie[u][i]]=trie[fail[u]][i];
                    q.push(trie[u][i]);
                }else trie[u][i]=trie[fail[u]][i];
            }
        }
    }

    void query(string s){
        int p=0;
        for(auto c:s){
            p=trie[p][c-'a'];
            s1[++top]=p;
            s2[top]=c;
            while(end[p]){
                top-=end[p];
                p=top?s1[top]:0;
            }
        }
    }

}


int main(){
    cin>>s>>n;
    for(int i=1;i<=n;i++){
        string awa;
        cin>>awa;
        ACAuto::insert(awa);
    }
    ACAuto::build();
    ACAuto::query(s);
    for(int i=1;i<=top;i++) cout<<s2[i];
    return 0;
}
