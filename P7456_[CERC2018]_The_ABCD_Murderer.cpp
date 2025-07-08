#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,L;
string s;

struct ACAuto{
    int nxt[MN][26],fail[MN],len[MN],dep[MN],tot;

    void insert(string s){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!nxt[p][k]){
                nxt[p][k]=++tot;
                dep[nxt[p][k]]=dep[p]+1;
            }
            p=nxt[p][k];
        }
        len[p]=dep[p];
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(nxt[0][i]) q.push(nxt[0][i]);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            len[u]=max(len[fail[u]],len[u]);
            for(int i=0;i<26;i++){
                int v=nxt[u][i];
                if(v){
                    fail[v]=nxt[fail[u]][i];
                    q.push(v);
                }else nxt[u][i]=nxt[fail[u]][i];
            }
        }
    }
}ac;

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=min(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l,t[p].r=r;
        t[p].val=1e9;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1,ret=1e9;
        if(mid>=fl) ret=min(ret,query(ls,fl,fr));
        if(mid<fr) ret=min(ret,query(rs,fl,fr));
        return ret;
    }

#undef ls
#undef rs
}sg;


int main(){
    cin>>L>>s;
    n=s.length();
    s=" "+s;
    for(int i=1;i<=L;i++){
        string st;
        cin>>st;
        ac.insert(st);
    }
    ac.build();
    sg.build(1,1,n);
    for(int i=1,p=0;i<=n;i++){
        int k=s[i]-'a';
        p=ac.nxt[p][k];
        int tmp;
        if(i-ac.len[p]>=1) tmp=sg.query(1,i-ac.len[p],i-1)+1;
        else tmp=1;
        sg.modify(1,i,tmp);
    }
    int ans=sg.query(1,n,n);
    if(ans>n) cout<<-1;
    else cout<<ans;
    return 0;
}
