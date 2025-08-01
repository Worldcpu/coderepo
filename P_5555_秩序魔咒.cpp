#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,m,ans,mxlen;
string s,t;

struct PAM{
    int len[MN],nxt[MN][26],fail[MN],cnt[MN],tot,lst;
    string st;

    PAM(){
        init();
    }

    void init(){
        fail[0]=1;
        len[1]=-1;
        tot=1;
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
        }
        lst=nxt[p][c];
        cnt[lst]++;
    }

    void build(){
        for(int i=1;i<st.length();i++){
            insert(st[i]-'a',i);
        }
        for(int i=tot;i>1;i--){
            cnt[fail[i]]+=cnt[i];
        }
    }
}pam[2];


void dfs(int x,int y){
    if(pam[0].len[x]>mxlen){
        mxlen=pam[0].len[x];
        ans=1;
    }else if(pam[0].len[x]==mxlen) ans++;
    for(int i=0;i<26;i++){
        if(pam[0].nxt[x][i]&&pam[1].nxt[y][i]){
            dfs(pam[0].nxt[x][i],pam[1].nxt[y][i]);
        }
    }
}

signed main(){
    cin>>n>>m>>s>>t;
    pam[0].st=" "+s,pam[1].st=" "+t;
    pam[0].build(),pam[1].build();
    dfs(0,0),dfs(1,1);
    cout<<mxlen<<" "<<ans;


    return 0;
}