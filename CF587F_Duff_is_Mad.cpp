#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int N=1e5+7;
int n,q,sumlen,MB,ans[N];
string s[N];
vector<int> adj[N];
vector<pir> L1[N],R1[N],L2[N],R2[N];

struct BIT{
    int t[N];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<N){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }
}bit;

namespace ACAuto{
    int trie[N][26],fail[N],fa[N],ed[N],tot=1;
    int sum[N],siz[N],dfn[N],dtot;

    void insert(string s,int id){
        int p=1;
        for(auto c:s){
            int k=c-'a';
            if(!trie[p][k]) trie[p][k]=++tot,fa[tot]=p;
            p=trie[p][k];
        }
        ed[id]=p;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(trie[1][i]) fail[trie[1][i]]=1,q.push(trie[1][i]);
            else trie[1][i]=1;
        }
        while(!q.empty()){
            int x=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                if(trie[x][i])
                    fail[trie[x][i]]=trie[fail[x]][i],q.push(trie[x][i]);
                else trie[x][i]=trie[fail[x]][i];
            }
        }
        for(int i=2;i<=tot;i++) adj[fail[i]].push_back(i);
    }

    void dfs1(int u){
        for(auto v:adj[u]){
            dfs1(v);
            sum[u]+=sum[v];
        }
    }

    void dfs2(int u){
        siz[u]=1;
        dfn[u]=++dtot;
        for(auto v:adj[u]){
            dfs2(v);
            siz[u]+=siz[v];
        }
    }
}using namespace ACAuto;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        sumlen+=s[i].length();
        insert(s[i],i);
    }
    build();
    MB=sumlen/sqrt(q*log2(sumlen));
    
    for(int i=1;i<=q;i++){
        int l,r,k;
        cin>>l>>r>>k;
        if(s[k].length()>MB){
            L1[k].emplace_back(l,i);
            R1[k].emplace_back(r,i);
        }else{
            L2[l].emplace_back(k,i);
            R2[r].emplace_back(k,i);
        }
    }

    for(int i=1;i<=n;i++){
        if(s[i].length()>MB){
            int p=ed[i];
            while(p!=1) sum[p]=1,p=fa[p];
            dfs1(1);
            sort(L1[i].begin(),L1[i].end());
            sort(R1[i].begin(),R1[i].end());
            reverse(L1[i].begin(),L1[i].end());
            reverse(R1[i].begin(),R1[i].end());
            int tmp=0;
            for(int j=1;j<=n;j++){
                while(L1[i].size()&&L1[i].back().first==j){
                    ans[L1[i].back().second]-=tmp;
                    L1[i].pop_back();
                }
                tmp+=sum[ed[j]];
                while(R1[i].size()&&R1[i].back().first==j){
                    ans[R1[i].back().second]+=tmp;
                    R1[i].pop_back();
                }
            }
            for(int i=2;i<=tot;i++) sum[i]=0;
        }
    }

    dfs2(1);
    for(int i=1;i<=n;i++){
        for(auto [k,id]:L2[i]){
            int p=ed[k];
            while(p!=1) ans[id]-=bit.query(dfn[p]),p=fa[p];
        }
        bit.modify(dfn[ed[i]],1);
        bit.modify(dfn[ed[i]]+siz[ed[i]],-1);
        for(auto [k,id]:R2[i]){
            int p=ed[k];
            while(p!=1) ans[id]+=bit.query(dfn[p]),p=fa[p];
        }
    }

    for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
    return 0;
}
