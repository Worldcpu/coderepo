#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=6e5+15;
constexpr ll MOD=1e9+7;
int n;
ll cf[MN];
string a,b,c;

struct gySAM{
    int nxt[MN][26],fa[MN],len[MN];
    ll cnt[MN][4],tot;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++) adj[i].clear();
        tot=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
    }

    gySAM(){
        init();
    }

    int newnode(int lst){
        int cur=++tot;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        cnt[cur][1]=cnt[cur][2]=cnt[cur][3]=0;
        return cur;
    }

    int clone(int from){
        int cur=++tot;
        fa[cur]=fa[from];
        cnt[cur][1]=cnt[cur][2]=cnt[cur][3]=0;
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    int extend(int c,int lst){
        if(nxt[lst][c]){
            int p=nxt[lst][c];
            if(len[p]==len[lst]+1) return p;
            else{
                int q=clone(p);
                len[q]=len[lst]+1;
                while(lst!=-1&&nxt[lst][c]==p) nxt[lst][c]=q,lst=fa[lst];
                fa[p]=q;
                return q;
            }
        }
        int cur=newnode(lst);
        len[cur]=len[lst]+1;
        while(lst!=-1&&!nxt[lst][c]) nxt[lst][c]=cur,lst=fa[lst];
        if(lst==-1) fa[cur]=0;
        else{
            int p=nxt[lst][c];
            if(len[p]==len[lst]+1) fa[cur]=p;
            else{
                int q=clone(p);
                len[q]=len[lst]+1;
                while(lst!=-1&&nxt[lst][c]==p) nxt[lst][c]=q,lst=fa[lst];
                fa[p]=fa[cur]=q;
            }
        }
        return cur;
    }

    void inittree(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
        }
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }

    void dfs(int u){
        for(auto v:adj[u]){
            dfs(v);
            for(int i=1;i<=3;i++) cnt[u][i]+=cnt[v][i];
        }
        cf[len[fa[u]]+1]=(cf[len[fa[u]]+1]+1ll*cnt[u][1]*cnt[u][2]%MOD*cnt[u][3]%MOD)%MOD;
        cf[len[u]+1]=(cf[len[u]+1]-1ll*cnt[u][1]*cnt[u][2]%MOD*cnt[u][3]%MOD+MOD)%MOD;
    }

    void insert(string s){
        int len=s.length();
        s=" "+s;
        for(int i=1,lst=0;i<=len;i++){
            lst=extend(s[i]-'a',lst);
        }
    }

    void add(string s,int id){
        int len=s.length();
        s=" "+s;
        for(int i=1,p=0;i<=len;i++){
            p=nxt[p][s[i]-'a'];
            cnt[p][id]++;
        }
    }

}sam;


int main(){
    cin>>a>>b>>c;
    sam.init();
    sam.insert(a);
    sam.insert(b);
    sam.insert(c);
    sam.add(a,1);
    sam.add(b,2);
    sam.add(c,3);
    sam.inittree();
    sam.dfs(0);
    for(int i=1;i<=min({a.length(),b.length(),c.length()});i++){
        (cf[i]+=cf[i-1])%=MOD;
        cout<<cf[i]<<" ";
    }
    return 0;
}

