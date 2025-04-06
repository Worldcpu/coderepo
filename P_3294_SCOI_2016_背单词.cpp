#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=1e5+15,MT=1e7+15;
struct trie{
    int son[26];
    int num;
    int isend;
}t[MT];
ll ans;
int n,cnt=1,pre[MN],siz[MN],id[MN],tot;
string str[MN];
vector<int> adj[MN];

bool cmp(int x,int y){
    return siz[x]<siz[y];
}

int root(int x){
    if(pre[x]==x) return x;
    else return pre[x]=root(pre[x]);
}

void insert(string s,int x){
    int now=0;
    for(int i=s.size()-1;i>=0;i--){
        int ch=s[i]-'a';
        if(!t[now].son[ch]){
            t[now].son[ch]=cnt++;
        }
        now=t[now].son[ch];
        t[now].num++;
    }
    t[now].isend=x;
}

void query(int now){
    for(int i=0;i<26;i++){
        if(t[now].son[i]){
            int v=t[now].son[i];
            if(!t[v].isend){
                pre[v]=root(now);
            }else{
                adj[t[root(now)].isend].push_back(t[v].isend);
            }
            query(v);
        }
    }
}

void dfs1(int u){
    siz[u]=1;
    for(auto v:adj[u]){
        dfs1(v);
        siz[u]+=siz[v];
    }
    sort(adj[u].begin(),adj[u].end(),cmp);
}

void dfs2(int u){
    id[u]=tot++;
    for(auto v:adj[u]){
        ans+=tot-id[u];
        dfs2(v);
    }
}

int main(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str[i];
        insert(str[i],i);
    }
    query(0);
    dfs1(0);
    dfs2(0);
    cout<<ans;
    return 0;
}