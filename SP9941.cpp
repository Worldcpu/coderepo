#include <bits/stdc++.h>
using namespace std;
constexpr int MN = 1000005; // 用于通用缓冲与数组界定（你可根据实际需要调整）
constexpr int TRIEN = 1000005; // trie/树相关上界（原代码用 MN 很大）
int n, w[MN], ans, Ctot;
string st[MN];
vector<int> adj[TRIEN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{ int l,r,val,tag; } t[TRIEN<<2];
    void pushup(int p){ t[p].val = max(t[ls].val, t[rs].val); }
    void dotag(int p,int k){ t[p].tag = max(t[p].tag,k); t[p].val = max(t[p].val,k); }
    void pushdown(int p){
        if(t[p].tag){
            dotag(ls,t[p].tag);
            dotag(rs,t[p].tag);
            t[p].tag = 0;
        }
    }
    void build(int p,int l,int r){
        t[p].l=l; t[p].r=r; t[p].tag=t[p].val=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }
    void modify(int p,int fl,int fr,int k){
        if(t[p].tag>=k) return;
        if(t[p].l>=fl && t[p].r<=fr){
            dotag(p,k); return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }
    int query(int p,int fl,int fr){
        if(t[p].l>=fl && t[p].r<=fr) return t[p].val;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1, ret=0;
        if(mid>=fl) ret = max(ret, query(ls,fl,fr));
        if(mid<fr) ret = max(ret, query(rs,fl,fr));
        return ret;
    }
} sg;

struct ACAuto{
    // 注意：TRIEN 必须足够大以容纳所有节点
    int t[TRIEN][26];
    int tot;
    int fail[TRIEN];
    int en[MN]; // en[i] = node index for string i
    void clear(){
        // 只清根节点并重置 tot
        memset(t[0], 0, sizeof t[0]);
        fail[0] = en[0] = 0;
        tot = 0;
    }
    void insert(const string &s, int x){
        int p = 0;
        for(char ch: s){
            int k = ch - 'a';
            if(!t[p][k]){
                t[p][k] = ++tot;
                // 初始化新节点数据，避免旧残留
                memset(t[tot], 0, sizeof t[tot]);
                fail[tot] = 0;
            }
            p = t[p][k];
        }
        en[x] = p;
    }
    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(t[0][i]){
                int v = t[0][i];
                fail[v] = 0;
                q.push(v);
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int i=0;i<26;i++){
                int v = t[u][i];
                if(v){
                    fail[v] = t[fail[u]][i];
                    q.push(v);
                }else{
                    t[u][i] = t[fail[u]][i];
                }
            }
        }
        for(int i=1;i<=tot;i++){
            adj[ fail[i] ].push_back(i);
        }
    }
} ac;

namespace Tree{
    int dfn[TRIEN], id[TRIEN], dtot, siz[TRIEN], fa[TRIEN];
    void dfs(int u,int pre){
        siz[u]=1;
        fa[u]=pre;
        dfn[u]=++dtot;
        id[dtot]=u;
        for(auto v: adj[u]){
            if(v==pre) continue;
            dfs(v,u);
            siz[u]+=siz[v];
        }
    }
}

void init(){
    ac.clear();
    ans = 0;
    Tree::dtot = 0;
    // 注意：adj 清理在所有 insert 完成、ac.tot 已知后进行
}

void solve(){
    scanf("%d", &n);
    init();
    static char buf[300050]; // 依据题目字符串最大长度调整
    for(int i=1;i<=n;i++){
        scanf("%s %d", buf, &w[i]);
        st[i] = string(buf);
        ac.insert(st[i], i);
    }
    // 此时 ac.tot 已知，清理 adj[0..ac.tot] 以防跨用例残留
    for(int i=0;i<=ac.tot;i++){
        adj[i].clear();
        Tree::dfn[i]=Tree::id[i]=Tree::siz[i]=Tree::fa[i]=0;
    }
    ac.build();
    Tree::dtot = 0;
    Tree::dfs(0,0);
    if(Tree::dtot <= 0) Tree::dtot = 1; // 保底，避免 seg.build( ,1,0)
    sg.build(1,1,Tree::dtot);
    for(int i=1;i<=n;i++){
        int u=0, ret=0;
        for(int j=0;j<(int)st[i].length();j++){
            u = ac.t[u][ st[i][j] - 'a' ];
            ret = max(ret, sg.query(1, Tree::dfn[u], Tree::dfn[u]));
        }
        ret += w[i];
        ans = max(ans, ret);
        sg.modify(1, Tree::dfn[u], Tree::dfn[u] + Tree::siz[u] - 1, ret);
    }
    printf("Case #%d: %d\n", ++Ctot, ans);
}

int main(){
    int T;
    if(scanf("%d", &T)!=1) return 0;
    while(T--){
        solve();
    }
    return 0;
}
