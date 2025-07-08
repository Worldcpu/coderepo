#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,r[MN],poss[MN];
long long ans;
int pre[31][MN];
char p[MN];
string s;

struct SAM{
    int nxt[MN][26],len[MN],c[MN],cnt[MN],id[MN],pos[MN],fa[MN],tot,lst;

    void init(){
        tot=lst=1;
    }

    int newnode(){
        int cur=++tot;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    int clone(int from){
        int cur=newnode();
        fa[cur]=fa[from];
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    void expand(int c){
        int cur=newnode();
        len[cur]=len[lst]+1;
        cnt[cur]=1;
        int p=lst;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int nq=clone(q);
                len[nq]=len[p]+1;
                fa[cur]=fa[q]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq,p=fa[p];
                }
            }
        }
        lst=cur;
    }

    void getsiz(){
        for(int i=1;i<=tot;i++) c[len[i]]++;
        for(int i=1;i<=n;i++) c[i]+=c[i-1];
        for(int i=1;i<=tot;i++) id[c[len[i]]--]=i;
        for(int i=tot;i>=1;i--){
            cnt[fa[id[i]]]+=cnt[id[i]];
        }
    }

    void initst(){
        for(int i=1;i<=tot;i++) pre[0][i]=fa[i];
        for(int i=1;i<=30;i++){
            for(int j=1;j<=tot;j++){
                pre[i][j]=pre[i-1][pre[i-1][j]];
            }
        }
    }

    void find(int l,int r){
        if(l<1||r>n) return;
        int slen=r-l+1,now=pos[r];
        for(int i=30;i>=0;i--){
            if(pre[i][now]&&len[pre[i][now]]>=slen) now=pre[i][now];
        }
        ans=max(ans,1ll*cnt[now]*(r-l+1));
    }
    
}sam;

void manacher(){
    p[++m]='@';
    for(int i=1;i<=n;i++){
        p[++m]='#';
        p[++m]=s[i];
        poss[m]=i;
    }
    p[++m]='#',p[++m]='$';
    int pos=0,mx=0;
    for(int i=1;i<=m;i++){
        if(i<mx) r[i]=min(mx-i,r[pos*2-i]);
        else r[i]=1;
        sam.find(poss[i-r[i]+2],poss[i+r[i]-2]);
        while(p[i-r[i]]==p[i+r[i]]){
            r[i]++;
            sam.find(poss[i-r[i]+2],poss[i+r[i]-2]);
        }
        if(i+r[i]>mx){
            mx=i+r[i],pos=i;
        }
    }
}

signed main(){
    cin>>s;
    sam.init();
    n=s.length();
    s=" "+s;
    for(int i=1;i<=n;i++){
        sam.expand(s[i]-'a');
        sam.pos[i]=sam.lst;
    }
    sam.initst();
    sam.getsiz();
    manacher();
    cout<<ans;

    return 0;
}
