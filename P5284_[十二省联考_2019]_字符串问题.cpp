#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,na,nb,m,in[MN],tot,dis[MN],a[MN],b[MN],last[MN],fa[MN],pre[31][MN],pos[MN];
long long ans;
bool isa[MN];
string s;
vector<int> adj[MN],g[MN];

struct SAM{
    int nxt[MN][26],len[MN],stot,lst;

    void init(){
        for(int i=0;i<=stot;i++){
            fa[i]=len[i]=0;
            for(int j=0;j<=30;j++) pre[j][i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        stot=lst=1;
    }

    void expand(int c){
        int cur=++stot;
        len[cur]=len[lst]+1;
        int p=lst;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int nq=++stot;
                len[nq]=len[p]+1;
                fa[nq]=fa[q];
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[q]=fa[cur]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }

    void initpre(){
        for(int i=1;i<=stot;i++) pre[0][i]=fa[i];
        for(int i=1;i<=30;i++){
            for(int j=2;j<=stot;j++){
                pre[i][j]=pre[i-1][pre[i-1][j]];
            }
        }
    }

}sam;

bool cmp(int x,int y){
    if(sam.len[x]==sam.len[y]){
        return isa[x]>isa[y];
    }
    return sam.len[x]>sam.len[y];
}

void init(){
    sam.init();
    for(int i=1;i<=tot;i++) in[i]=dis[i]=isa[i]=pos[i]=0,g[i].clear(),adj[i].clear();
    ans=0;
}

int toposort(){
    queue<int> q;
    for(int i=1;i<=tot;i++) if(!in[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ans=max(ans,1ll*dis[u]+sam.len[u]);
        for(auto v:adj[u]){
            dis[v]=max(dis[v],dis[u]+sam.len[u]);
            in[v]--;
            if(!in[v]){
                q.push(v);
            }
        }
    }
    bool flag=0;
    for(int i=1;i<=tot;i++){
        if(in[i]) flag=1;
    }
    if(flag) return -1;
    return ans;
}

void solve(){
    init();
    cin>>s;
    n=s.length();
    s=" "+s;
    for(int i=n;i>=1;i--){
        sam.expand(s[i]-'a');
        pos[i]=sam.lst;
    }
    sam.initpre();
    cin>>na;
    tot=sam.stot;
    for(int i=1;i<=na;i++){
        int l,r;
        cin>>l>>r;
        int lenn=r-l+1,p=pos[l];
        for(int i=30;i>=0;i--){
            if(pre[i][p]&&sam.len[pre[i][p]]>=lenn) p=pre[i][p]; 
        }
        isa[++tot]=1;
        sam.len[tot]=lenn;
        g[p].push_back(tot);
        a[i]=tot;
    }
    cin>>nb;
    for(int i=1;i<=nb;i++){
        int l,r;
        cin>>l>>r;
        int lenn=r-l+1,p=pos[l];
        for(int i=30;i>=0;i--){
            if(pre[i][p]&&sam.len[pre[i][p]]>=lenn) p=pre[i][p]; 
        }
        isa[++tot]=0;
        sam.len[tot]=lenn;
        g[p].push_back(tot);
        b[i]=tot;
    }
    for(int i=2;i<=sam.stot;i++) sort(g[i].begin(),g[i].end(),cmp);
    for(int i=1;i<=sam.stot;i++){
        int lst=i;
        for(int j=g[i].size()-1;j>=0;j--){
            adj[lst].push_back(g[i][j]);
            in[g[i][j]]++;
            if(!isa[g[i][j]]) lst=g[i][j];
        }
        last[i]=lst;
    }
    for(int i=2;i<=sam.stot;i++){
        adj[last[fa[i]]].push_back(i);
        in[i]++;
    }
    for(int i=1;i<=tot;i++){
        if(!isa[i]) sam.len[i]=0;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        adj[a[x]].push_back(b[y]);
        in[b[y]]++;
    }
    cout<<toposort()<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
