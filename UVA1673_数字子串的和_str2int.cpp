#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=2012;
int n,f[MN],g[MN];

struct gySAM{
    int nxt[MN][26],c[MN],id[MN],fa[MN],len[MN],mxl,tot;
    vector<int> adj[MN];

    void init(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
            fa[i]=g[i]=f[i]=len[i]=c[i]=id[i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        tot=1;
        mxl=0;
        g[1]=1;
    }

    gySAM(){
        init();
    }

    int newnode(){
        int cur=++tot;
        f[cur]=g[cur]=0;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    int clone(int from){
        int cur=newnode();
        fa[cur]=fa[from];
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    int extend(int c,int lst){
        if(nxt[lst][c]&&len[nxt[lst][c]]==len[lst]+1) return nxt[lst][c];
        int cur=newnode(),p=lst,flag=0,q,nq;
        len[cur]=len[p]+1;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                if(p==lst) flag=1,cur=0,tot--;
                nq=clone(q);
                len[nq]=len[p]+1;
                fa[q]=fa[cur]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        return flag?nq:cur;
    }

    void insert(string s){
        int len=s.length(),lst=1;
        s=" "+s;
        mxl=max(mxl,len);
        for(int i=1;i<=len;i++){
            lst=extend(s[i]-'0',lst);
        }
    }

    void initc(){
		for(int i=1; i<=tot; ++i) c[len[i]]++;
		for(int i=0; i<=mxl; ++i) c[i]=0;
		for(int i=1; i<=tot; ++i) c[len[i]]++;
		for(int i=1; i<=mxl; ++i) c[i]+=c[i-1];
		for(int i=1; i<=tot; ++i) id[c[len[i]]--]=i;    
    }

    void solve(){
        for(int i=1;i<=tot;i++){
            int u=id[i];
            cerr<<u<<" ";
            for(int j=0;j<10;j++){
                if((u==1&&!j)||!nxt[u][j]) continue;
                (f[nxt[u][j]]+=g[u]*j+f[u]*10)%=MOD;
                (g[nxt[u][j]]+=g[u])%=MOD;
            }
        }
    }
}sam;


void solve(){
    sam.init();
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        sam.insert(s);
    }
    sam.initc();
    sam.solve();
    int ans=0;
    for(int i=1;i<=sam.tot;i++) (ans+=f[i])%=MOD;
    cout<<ans<<'\n';
}

signed main(){
    while(cin>>n){
        solve();
    }

    return 0;
}
