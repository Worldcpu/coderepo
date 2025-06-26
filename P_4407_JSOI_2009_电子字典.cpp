#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;
int n,m;
map<string,int> mp;

struct Trie{
    int tot,trie[MN][26];
    int end[MN];
    bool vis[MN];


    void insert(string s){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!trie[p][k]) trie[p][k]=++tot;
            p=trie[p][k];
        }
        end[p]++;
    }

    int dfs(string s,int u,int pos,bool lim){
        if(pos==s.length()&&!vis[u]&&end[u]&&lim){
            vis[u]=1;
            return end[u];
        }
        int ret=0;
        if(trie[u][s[pos]-'a']) dfs(s,trie[u][s[pos]-'a'],pos+1,lim);
        if(lim) return ret;
        ret+=dfs(s,u,pos+1,1);
        for(int i=0;i<26;i++){
            if(trie[u][i]){
                ret+=dfs(s,trie[u][i],pos+1,1);
                ret+=dfs(s,trie[u][i],pos,1);
            }
        }
        return ret;
    }

    int solve(string s){
        if(mp.count(s)) return -1;
        memset(vis,0,sizeof(vis));
        cerr<<"AWA\n";
        return dfs(s,0,0,0);
    }

}t;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        t.insert(s);
        mp[s]++;
    }
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        cout<<t.solve(s)<<'\n';
    }

    return 0;
}
