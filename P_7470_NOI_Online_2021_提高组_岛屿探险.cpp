#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=500000+15; // 由你指定；程序中其他容量基于 MN 的倍数
int n,q,b[MN],ql[MN],qr[MN],c[MN],d[MN],a[MN],ans[MN],lsan[MN],ltot,qqtot;
int rt[MN];
pir qry[MN];

// 使用 MN 的倍数作为节点上限（保守）
const int TRIE_NODES = MN * 25; // 足够大的上限（24 位 * 最大元素数）
// 持久化字典树（修正版）
struct KCJTrie{
    struct Node{
        int ch[2];
        int siz;
    };
    Node t[TRIE_NODES];
    int tot;
    KCJTrie(){ tot = 0; /* t[0] 默认为 0 */ }

    // newnode: 复制索引 x 的节点（x 可以为 0）
    int newnode(int x){
        int p = ++tot;
        t[p] = t[x];
        return p;
    }

    // 插入：p 为新 root 输出，pre 为旧 root 输入（可为 0）
    void insert(int &p, int pre, int val){
        p = newnode(pre);
        t[p].siz++;
        int cur = p;
        for(int i = 23; i >= 0; --i){
            int k = (val >> i) & 1;
            int old_child = t[pre].ch[k]; // 旧 child（可能为0）
            int new_child = newnode(old_child); // 复制旧 child
            t[cur].ch[k] = new_child; // 把新 child 挂回父节点
            t[new_child].siz++;
            // descend
            cur = new_child;
            pre = old_child;
        }
    }

    // query: 与原逻辑保持一致，安全地访问 child
    int query(int x, int y, int C, int D){
        int res = 0;
        for(int i = 23; i >= 0; --i){
            if (!x) break;
            int ck = (C >> i) & 1;
            int dk = (D >> i) & 1;
            if (dk){
                int cx = t[x].ch[ck];
                int cy = t[y].ch[ck];
                int sx = (cx ? t[cx].siz : 0);
                int sy = (cy ? t[cy].siz : 0);
                res += sx - sy;
            }
            int nx = (x ? t[x].ch[ck ^ dk] : 0);
            int ny = (y ? t[y].ch[ck ^ dk] : 0);
            x = nx; y = ny;
        }
        if (x) res += t[x].siz;
        if (y) res -= t[y].siz;
        return res;
    }
} t1;

struct Trie{
    int nxt[TRIE_NODES][2];
    int siz[TRIE_NODES];
    int tot;

    void init(){
        nxt[0][0] = nxt[0][1] = 0;
        siz[0] = 0;
        tot = 0;
    }

    void insert_val(int x){
        int p = 0;
        for(int i = 23; i >= 0; --i){
            int k = (x >> i) & 1;
            if (!nxt[p][k]) {
                ++tot;
                nxt[p][k] = tot;
                nxt[tot][0] = nxt[tot][1] = 0;
                siz[tot] = 0;
            }
            p = nxt[p][k];
        }
    }

    void dosiz(int C, int D){
        int p = 0;
        for(int i = 23; i >= 0; --i){
            int ck = (C >> i) & 1;
            int dk = (D >> i) & 1;
            if (dk){
                int node = nxt[p][ck];
                if (node) siz[node]++;
            }
            p = nxt[p][ck ^ dk];
            if (!p) break;
        }
        if (p) siz[p]++;
    }

    int query_val(int v){
        int p = 0;
        int ret = 0;
        for(int i = 23; i >= 0; --i){
            ret += (p ? siz[p] : 0);
            int k = (v >> i) & 1;
            p = (p ? nxt[p][k] : 0);
            if (!p) break;
        }
        ret += (p ? siz[p] : 0);
        return ret;
    }
} t2;

pir qq[MN * 3];

void cdq(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);

    ltot = 0;
    for(int i = mid+1;i<=r;i++){
        if(qry[i].second > n) continue;
        lsan[++ltot] = qry[i].second;
    }
    if (ltot > 0) sort(lsan+1, lsan+1+ltot);

    t1.tot = 0;
    rt[0] = 0;
    for(int i = 1;i<=ltot;i++){
        int idx = lsan[i];
        t1.insert(rt[i], rt[i-1], a[idx]);
    }

    for(int i = l;i<=mid;i++){
        if (qry[i].second <= n) continue;
        int pos = qry[i].second - n;
        int L = lower_bound(lsan+1, lsan+1+ltot, ql[pos]) - lsan;
        int R = upper_bound(lsan+1, lsan+1+ltot, qr[pos]) - lsan - 1;
        if (L > R) continue;
        ans[pos] += t1.query(rt[R], rt[L-1], c[pos], d[pos]);
    }

    t2.init();
    qqtot = 0;
    for(int i = mid+1;i<=r;i++){
        if (qry[i].second <= n) continue;
        int pos = qry[i].second - n;
        t2.insert_val(c[pos]);
        qq[++qqtot] = pir(ql[pos]-1, pos + n);
        qq[++qqtot] = pir(qr[pos], pos + n + q);
    }
    for(int i = l;i<=mid;i++){
        if (qry[i].second > n) continue;
        qq[++qqtot] = pir(qry[i].second, qry[i].second);
    }
    sort(qq+1, qq+1+qqtot);

    for(int i = 1;i<=t2.tot;i++) t2.siz[i] = 0;
    t2.siz[0] = 0;
    for(int i = 1;i<=qqtot;i++){
        if (qq[i].second <= n){
            int idx = qq[i].second;
            t2.dosiz(a[idx], b[idx]);
        } else if (qq[i].second <= n + q){
            int pos = qq[i].second - n;
            ans[pos] -= t2.query_val(c[pos]);
        } else {
            int pos = qq[i].second - n - q;
            ans[pos] += t2.query_val(c[pos]);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        qry[i]=pir(b[i],i);
    }
    for(int i=1;i<=q;i++){
        cin>>ql[i]>>qr[i]>>c[i]>>d[i];
        qry[i+n]=pir(d[i],i+n);
    }
    sort(qry+1,qry+1+n+q);
    cdq(1,n+q);
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}
