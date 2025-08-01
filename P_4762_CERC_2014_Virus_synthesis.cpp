#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,ans,f[MN];
string s;

struct PAM{
    int len[MN],nxt[MN][26],fail[MN],cnt[MN],half[MN],tot,lst;
    string st;

    PAM(){
        init();
    }

    void init(){
        for(int i=0;i<=tot;i++){
            memset(nxt[i],0,sizeof(nxt[i]));
            fail[i]=len[i]=half[i]=0;
            f[i]=0;
        }
        fail[0]=1;
        len[1]=-1;
        tot=1;
        lst=0;
    }

    int getfail(int u,int p){
        while(p-len[u]-1<=0||st[p-len[u]-1]!=st[p]){
            u=fail[u];
        }
        return u;
    }

    void insert(int c,int id){
        int p=getfail(lst,id);
        if(!nxt[p][c]){
            fail[++tot]=nxt[getfail(fail[p],id)][c];
            nxt[p][c]=tot;
            len[tot]=len[p]+2;
            if(len[tot]<=2) half[tot]=fail[tot];
            else{
                int hp=half[p];
                while(st[p-len[hp]-1]!=st[p]||(len[hp]+2<<1)>len[tot]){
                    hp=fail[hp];
                }
                half[tot]=nxt[hp][c];
            }
        }
        lst=nxt[p][c];
    
    }

    void build(){
        for(int i=1;i<st.length();i++){
            insert(st[i]-'A',i);
        }
    }
}pam;

void bfs(){
    queue<int> q;
    q.push(0);
    f[0]=1;
    for(int i=1;i<=pam.tot;i++) f[i]=pam.len[i];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            int v=pam.nxt[u][i],hf=pam.half[v];
            if(!v) continue;
            f[v]=f[u]+1;
            f[v]=min(f[v],f[hf]+1+(pam.len[v]>>1)-pam.len[hf]);
            ans=min(ans,n-pam.len[v]+f[v]);
            q.push(v);
        }
    }
}

void init(){
    pam.init();
    ans=n;
}

void solve(){
    cin>>s;
    n=s.length();
    s=" "+s;
    init();
    pam.st=s;
    pam.build();
    bfs();
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}