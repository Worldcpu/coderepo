#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e6+15, INF=1e9;

int nn, q, n, m=400000;
int sa[N], ra[N], h[N], t1[N], t2[N], c[N];
int st[20][N], lg[N];
int s[N], col[N], hd[N], len[N], bu[N];
int pre[N], ans1[N], ans2[N];
int lp[N]; 
struct Query { int id, l, r; } qry[N];

struct BIT {
    int t[N];
    
    void clear() {
        memset(t, 0, sizeof(t));
    }
    
    void upd(int i, int v) {
        if (i) for (; i<=n; i+=i&-i) t[i] += v;
    }
    
    int query(int i) {
        int res = 0;
        for (; i; i-=i&-i) res += t[i];
        return res;
    }
    
    int query(int l, int r) {
        return query(r) - query(l-1);
    }
} bit1, bit2;

void getsa() {
    int *x = t1, *y = t2;
    memset(c, 0, sizeof(c));
    for (int i=1; i<=n; ++i) ++c[x[i]=s[i]];
    for (int i=1; i<=m; ++i) c[i] += c[i-1];
    for (int i=n; i>=1; --i) sa[c[x[i]]--] = i;
    
    for (int k=1; k<=n; k<<=1) {
        int p = 0;
        memset(c, 0, sizeof(c));
        for (int i=n-k+1; i<=n; ++i) y[++p] = i;
        for (int i=1; i<=n; ++i) if (sa[i]>k) y[++p] = sa[i]-k;
        
        for (int i=1; i<=n; ++i) ++c[x[y[i]]];
        for (int i=1; i<=m; ++i) c[i] += c[i-1];
        for (int i=n; i>=1; --i) sa[c[x[y[i]]]--] = y[i];
        
        swap(x, y);
        x[sa[1]] = 1;
        for (int i=2; i<=n; ++i)
            x[sa[i]] = x[sa[i-1]] + (y[sa[i]]!=y[sa[i-1]] || y[sa[i]+k]!=y[sa[i-1]+k]);
        if ((m=x[sa[n]]) >= n) break;
    }
    for (int i=1; i<=n; ++i) ra[sa[i]] = i;
}

void geth() {
    for (int i=1, k=0; i<=n; ++i) {
        if (k) --k;
        int j = sa[ra[i]-1];
        while (s[i+k] == s[j+k]) ++k;
        h[ra[i]] = k;
    }
}

void initST() {
    for (int i=1; i<=n; ++i) st[0][i] = h[i];
    for (int i=1; (1<<i)<=n; ++i) lg[1<<i] = i;
    for (int i=1; i<=n; ++i) if (!lg[i]) lg[i] = lg[i-1];
    for (int i=1; i<20; ++i)
        for (int j=1; j+(1<<i)-1<=n; ++j)
            st[i][j] = min(st[i-1][j], st[i-1][j+(1<<(i-1))]);
}

int getmin(int a, int b) {
    if (a == b) return INF;
    if (a > b) swap(a, b);
    int d = lg[b-(a++)];
    return min(st[d][a], st[d][b-(1<<d)+1]);
}

bool cmp(Query a, Query b) {
    return a.r < b.r;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> nn >> q;
    int x, c = 10000;
    for (int i=1; i<=nn; ++i) {
        for (int j=0; j<2; ++j) {
            int len; cin >> len;
            while (len--) {
                cin >> x;
                s[++n] = x;
                col[n] = i;
            }
            s[++n] = ++c;
        }
    }
    for (int i=1; i<=q; ++i) {
        cin >> len[n+1];
        hd[n+1] = i;
        for (int j=len[n+1]; j--; ) {
            cin >> x;
            s[++n] = x;
            col[n] = -i;
        }
        s[++n] = ++c;
    }
    getsa();
    geth();
    initST();
    for (int i=1; i<=n; ++i) {
        if (col[sa[i]] > 0) {
            pre[i] = bu[col[sa[i]]];
            bu[col[sa[i]]] = i;
        }
        if (hd[i]) {
            qry[hd[i]].id = hd[i];
            int l=1, r=ra[i];
            while (l < r) {
                int mi = (l+r)>>1;
                if (getmin(mi, ra[i]) >= len[i]) r = mi;
                else l = mi+1;
            }
            qry[hd[i]].l = lp[hd[i]] = l;
            l = ra[i], r = n;
            while (l < r) {
                int mi = (l+r+1)>>1;
                if (getmin(ra[i], mi) >= len[i]) l = mi;
                else r = mi-1;
            }
            qry[hd[i]].r = r;
        }
    }
    sort(qry+1, qry+q+1, cmp);
    sort(lp+1, lp+q+1);
    for (int i=1, j=1, k=1; i<=n; ++i) {
        for (; j<=q && lp[j]==i; ++j) bit2.upd(i, 1);
        if (col[sa[i]] > 0) {
            ans2[col[sa[i]]] += bit2.query(i) - bit2.query(pre[i]);
            bit1.upd(i, 1);
            bit1.upd(pre[i], -1);
        }
        for (; k<=q && qry[k].r==i; ++k) {
            ans1[qry[k].id] = bit1.query(qry[k].l, qry[k].r);
            bit2.upd(qry[k].l, -1);
        }
    }
    for (int i=1; i<=q; ++i) cout << ans1[i] << "\n";
    for (int i=1; i<=nn; ++i) cout << ans2[i] << " ";
    return 0;
}
