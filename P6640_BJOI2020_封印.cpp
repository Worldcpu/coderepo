#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=3e6+15;
int n,m,q,st[MN][30],L[MN];
string s,t;

struct SAM{
    int nxt[MN][26],fa[MN],len[MN],cnt[MN],tot,lst;
    int cnt_init[MN];
    vector<int> adj[MN];

    void init(){
        tot=0;
        lst=0;
        fa[0]=-1;
        len[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
        cnt_init[0]=0;
    }

    int newnode(){
        int cur=++tot;
        cnt_init[cur]=1;
        memset(nxt[cur],0,sizeof(nxt[cur]));
        return cur;
    }

    int clone(int from){
        int cur=++tot;
        fa[cur]=fa[from];
        cnt_init[cur]=0;
        memcpy(nxt[cur],nxt[from],sizeof(nxt[from]));
        return cur;
    }

    void extend(int c){
        int cur=newnode();
        len[cur]=len[lst]+1;
        int p=lst;
        while(p!=-1&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(p==-1) fa[cur]=0;
        else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1) fa[cur]=q;
            else{
                int nq=clone(q);
                len[nq]=len[p]+1;
                while(p!=-1&&nxt[p][c]==q) nxt[p][c]=nq,p=fa[p];
                fa[q]=fa[cur]=nq;
            }
        }
        lst=cur;
    }

    void inittree(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
            cnt[i]=-1;
        }
        for(int i=1;i<=tot;i++){
            adj[fa[i]].push_back(i);
        }
    }
}sam;

void getL(){
    int p=0;
    for(int i=1;i<=n;i++){
        int k=s[i]-'a';
        if(sam.nxt[p][k]){
            p=sam.nxt[p][k];
            L[i]=L[i-1]+1;
        }else{
            while(p!=-1&&!sam.nxt[p][k]){
                p=sam.fa[p];
            }
            if(p==-1){
                p=0;
            }else{
                L[i]=sam.len[p]+1;
                p=sam.nxt[p][k];
            }
        }
    }
}

void inist(){
    for(int i=1;i<=n;i++) st[i][0]=L[i];
    for(int j=1;j<=20;j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}

int query(int l,int r){
    if(l>r) return 0;
    int lg=__lg(r-l+1);
    return max(st[l][lg],st[r-(1<<lg)+1][lg]);
}

int getpos(int l,int r){
    int len=l,ret=r+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(mid-L[mid]+1>=len){
            r=mid-1;
            ret=mid;
        }else l=mid+1;
    }
    return ret;
}

int main(){
    cin>>s>>t>>q;
    n=s.length(),m=t.length();
    s=" "+s,t=" "+t;
    sam.init();
    for(int i=1;i<=m;i++) sam.extend(t[i]-'a');
    getL();
    inist();
    while(q--){
        int l,r,pos;
        cin>>l>>r;
        pos=getpos(l,r);
        cout<<max(query(pos,r),pos-l)<<'\n';
    }
    return 0;
}
