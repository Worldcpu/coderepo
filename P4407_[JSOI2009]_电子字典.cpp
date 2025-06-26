#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,m;
bool vis[MN];
map<string,bool> mp;


struct Trie{
    int t[MN][26],tot;
    int end[MN];

    void insert(string s){
        int p=0;
        mp[s]=1;
        for(auto c:s){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[p]++;
    }

    int dfs(string s,int u,int pos,bool lim){
        if(pos==s.length()&&end[u]&&!vis[u]&&lim){
            vis[u]=1;
            return end[u];
        }
        int ret=0,k=s[pos]-'a';
        if(t[u][k]) ret+=dfs(s,t[u][k],pos+1,lim);
        if(lim) return ret;
        ret+=dfs(s,u,pos+1,1);
        for(int i=0;i<26;i++){
            if(t[u][i]){
                ret+=dfs(s,t[u][i],pos+1,1);
                ret+=dfs(s,t[u][i],pos,1);
            }
        }
        return ret;
    }

    int solve(string s){
        if(mp.count(s)) return -1;
        memset(vis,0,sizeof(vis));
        return dfs(s,0,0,0);
    }
    
}t;


int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        t.insert(s);
    }
    while(m--){
        string s;
        cin>>s;
        cout<<t.solve(s)<<'\n';
    }

    return 0;
}
