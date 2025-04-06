#include<bits/stdc++.h>
using namespace std;
const int MN=256;
int n,m,cst[MN],fa[MN],siz[MN];
unordered_map<string,int> mp;
string s,s1,s2;
vector<int> adj[MN];
vector<string> sadj[MN];
int f[MN][MN]{};

void dfs(int u){
    f[u][0]=0;
    siz[u]=1;
    for(auto v:adj[u]){
        dfs(v);
        siz[u]+=siz[v];
        for(int i=siz[u];i>=1;i--){
            for(int j=1;j<=i;j++){
                f[u][i]=min(f[u][i],f[u][i-j]+f[v][j]);
            }
        }
    }
    f[u][siz[u]]=min(f[u][siz[u]],cst[u]);
}

void init(){
    mp.clear();
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<=n;i++){
        adj[i].clear();
        fa[i]=0;
        cst[i]=0;
        sadj[i].clear();
    }
}

int main(){
    while (1)
    {
        getline(cin,s);
        if(s=="#") break;
        stringstream ss1;
        ss1<<s;
        ss1>>n>>m;
        init();
        for(int i=1;i<=n;i++){
            getline(cin,s);
            stringstream ss2;
            ss2<<s;
            ss2>>s1>>cst[i];
            mp[s1]=i;
            while(ss2>>s2){
                sadj[i].push_back(s2);
            }
        }
        for(int i=1;i<=n;i++){
            for(auto v:sadj[i]){
                adj[i].push_back(mp[v]);
                fa[mp[v]]++;
            }
        }
        for(int i=1;i<=n;i++){
            if(!fa[i]) adj[0].push_back(i);
        }
        dfs(0);
        int ans=1e9;
        for(int i=m;i<=n;i++){
            ans=min(ans,f[0][i]);
        }
        cout<<ans<<'\n';
    }
    
    return 0;
}