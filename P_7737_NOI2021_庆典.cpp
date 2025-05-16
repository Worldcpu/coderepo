#include <bits/stdc++.h>
using namespace std;
constexpr int MN = 4e5 + 15, MV = 100;
int n, m, S, T, q, K, vdcc, in1[MN], in2[MN], sum[MN], col[MN], colw[MN];

struct Edge {
    int to, nxt;
};
struct Graph {
    int head[MN], cnt;
    Edge e[MN * 2];
    void add(int u, int v) {
        e[++cnt].to = v;
        e[cnt].nxt = head[u];
        head[u] = cnt;
    }
} adj, g1, g2;

struct graph {
    int head[20], cnt;
    struct Edge {
        int to, nxt, v;
    } e[60];
    void add(int u, int v, int w) {
        e[++cnt].to = v;
        e[cnt].nxt = head[u];
        e[cnt].v = w;
        head[u] = cnt;
    }
    void clear() {
        cnt = 0;
        memset(head, 0, sizeof(head));
    }
} g3, g4;

namespace ly {
    namespace IO {
        #ifndef LOCAL
            constexpr auto maxn = 1 << 20;
            char in[maxn], out[maxn], *p1 = in, *p2 = in, *p3 = out;
            #define getchar() (p1 == p2 && (p2 = (p1 = in) + fread(in, 1, maxn, stdin), p1 == p2) ? EOF : *p1++)
            #define flush() (fwrite(out, 1, p3 - out, stdout))
            #define putchar(x) (p3 == out + maxn && (flush(), p3 = out), *p3++ = (x))
            class Flush { public: ~Flush() { flush(); } } _;
        #endif
        namespace usr {
            template<typename type>
            inline type read(type &x) {
                x = 0; bool flag(0); char ch = getchar();
                while (!isdigit(ch)) flag ^= ch == '-', ch = getchar();
                while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
                return flag ? x = -x : x;
            }
            template<typename type>
            inline void write(type x) {
                x < 0 ? x = -x, putchar('-') : 0;
                static short Stack[50], top(0);
                do Stack[++top] = x % 10, x /= 10; while (x);
                while (top) putchar(Stack[top--] | 48);
            }
            inline char read(char &x) { do x = getchar(); while (isspace(x)); return x; }
            inline void read(char *x) { static char ch; read(ch); do *(x++) = ch; while (!isspace(ch = getchar()) && ~ch); }
            template<typename type> inline void write(type *x) { while (*x) putchar(*(x++)); }
            inline void read(string &x) { static char ch; read(ch), x.clear(); do x += ch; while (!isspace(ch = getchar()) && ~ch); }
            inline void write(const string &x) { for (int i = 0; i < x.length(); ++i) putchar(x[i]); }
            template<typename type, typename... T> inline void read(type &x, T &... y) { read(x), read(y...); }
            template<typename type, typename... T> inline void write(const type &x, const T &... y) { write(x), putchar(' '), write(y...); }
            template<typename type> inline void put(const type &x, bool flag = 1) { write(x); if (flag) putchar('\n'); else putchar(' '); }
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    } using namespace IO::usr;
} using namespace ly::IO::usr;

struct Hash {
    unordered_map<int, int> ump;
    int tot;
    void clear() { ump.clear(); tot = 0; }
    int getid(int x) { return ump[x] ? ump[x] : (ump[x] = ++tot); }
} H;

struct Tarjan {
    int s[MN], top, dfn[MN], low[MN], tot;
    bool vis[MN];

    void tarjan(int u) {
        dfn[u] = low[u] = ++tot;
        s[++top] = u;
        vis[u] = 1;
        for (int j = adj.head[u]; j; j = adj.e[j].nxt) {
            int v = adj.e[j].to;
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (vis[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            int p;
            vdcc++;
            do {
                p = s[top--];
                col[p] = vdcc;
                colw[vdcc]++;
                vis[p] = 0;
            } while (p != u);
        }
    }

    void getg2() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) tarjan(i);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = adj.head[i]; j; j = adj.e[j].nxt) {
                int v = adj.e[j].to;
                if (col[i] != col[v]) {
                    g1.add(col[i], col[v]);
                    in1[col[v]]++;
                }
            }
        }
    }
} tj;

void toposort() {
    queue<int> q;
    for (int i = 1; i <= vdcc; i++) {
        if (!in1[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int j = g1.head[u]; j; j = g1.e[j].nxt) {
            int v = g1.e[j].to;
            in1[v]--;
            if (!in1[v]) {
                g2.add(u, v);
                in2[v]++;
                q.push(v);
            }
        }
    }
}

struct Tree {
    int dfn[MN], siz[MN], dep[MN], fa[MN], htop[MN], hson[MN], rt, tot;
    void getrt() {
        for (int i = 1; i <= vdcc; i++) {
            if (!in2[i]) rt = i;
        }
    }

    void dfs1(int u, int pre) {
        fa[u] = pre;
        dep[u] = dep[pre] + 1;
        dfn[u] = ++tot;
        sum[u] = sum[pre] + colw[u];
        siz[u] = 1;
        for (int j = g2.head[u]; j; j = g2.e[j].nxt) {
            int v = g2.e[j].to;
            if (v == pre) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[hson[u]] < siz[v]) hson[u] = v;
        }
    }

    void dfs2(int u, int ltop) {
        htop[u] = ltop;
        if (!hson[u]) return;
        dfs2(hson[u], ltop);
        for (int j = g2.head[u]; j; j = g2.e[j].nxt) {
            int v = g2.e[j].to;
            if (v == fa[u] || v == hson[u]) continue;
            dfs2(v, v);
        }
    }

    int lca(int x, int y) {
        while (htop[x] != htop[y]) {
            if (dep[htop[x]] < dep[htop[y]]) swap(x, y);
            x = fa[htop[x]];
        }
        return dep[x] < dep[y] ? x : y;
    }
} t;

struct SOLVE {
    int h[MN], val[60], s[MN], top, tot3, tot4;
    bool vis[30], vis2[30], vp[30];

    void clear() {
        top = 0;
        tot3 = tot4 = 0;
        g3.clear();
        g4.clear();
        H.clear();
        memset(val, 0, sizeof val);
    }

    void getvt() {
        sort(h + 1, h + (K + 1) * 2 + 1, [&](int x, int y) {
            return t.dfn[x] < t.dfn[y];
        });
        int tot = unique(h + 1, h + (K + 1) * 2 + 1) - h - 1;
        for (int i = 1; i <= tot; i++) {
            val[H.getid(h[i])] = colw[h[i]];
        }
        s[++top] = h[1];
        for (int i = 2; i <= tot; i++) {
            int qlca = t.lca(h[i], s[top]);
            val[H.getid(qlca)] = colw[qlca];
            while (1) {
                if (t.dep[qlca] >= t.dep[s[top - 1]]) {
                    if (qlca != s[top]) {
                        g3.add(H.getid(qlca), H.getid(s[top]), sum[t.fa[s[top]]] - sum[qlca]);
                        g4.add(H.getid(s[top]), H.getid(qlca), sum[t.fa[s[top]]] - sum[qlca]);
                        if (qlca != s[top - 1]) s[top] = qlca;
                        else top--;
                    }
                    break;
                } else {
                    g3.add(H.getid(s[top - 1]), H.getid(s[top]), sum[t.fa[s[top]]] - sum[s[top - 1]]);
                    g4.add(H.getid(s[top]), H.getid(s[top - 1]), sum[t.fa[s[top]]] - sum[s[top - 1]]);
                    top--;
                }
            }
            s[++top] = h[i];
        }
        while (top - 1) {
            g3.add(H.getid(s[top - 1]), H.getid(s[top]), sum[t.fa[s[top]]] - sum[s[top - 1]]);
            g4.add(H.getid(s[top]), H.getid(s[top - 1]), sum[t.fa[s[top]]] - sum[s[top - 1]]);
            top--;
        }
    }

    int work() {
        memset(vis, 0, sizeof vis);
        memset(vp, 0, sizeof vp);
        memset(vis2, 0, sizeof vis2);
        queue<int> q;
        q.push(H.getid(S));
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vp[u] = 1;
            for (int j = g3.head[u]; j; j = g3.e[j].nxt) {
                int v = g3.e[j].to;
                if (!vis[j]) {
                    vis[j] = 1;
                    q.push(v);
                }
            }
        }
        int ans = 0;
        q.push(H.getid(T));
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (vp[u]) {
                ans += val[u];
                vp[u] = 0;
            }
            for (int j = g4.head[u]; j; j = g4.e[j].nxt) {
                int v = g4.e[j].to;
                if (!vis2[j]) {
                    vis2[j] = 1;
                    if (vis[j]) {
                        ans += g4.e[j].v;
                        vis[j] = 0;
                    }
                    q.push(v);
                }
            }
        }
        return ans;
    }

    void solve() {
        clear();
        read(S), read(T);
        S = col[S];
        T = col[T];
        h[1] = S;
        h[2] = T;
        for (int i = 1; i <= K; i++) {
            int u, v;
            read(u), read(v);
            u = col[u];
            v = col[v];
            g3.add(H.getid(u), H.getid(v), 0);
            g4.add(H.getid(v), H.getid(u), 0);
            h[i * 2 + 1] = u;
            h[i * 2 + 2] = v;
        }
        getvt();
        put(work());
    }
} sol;

int main() {
    read(n);
    read(m);
    read(q);
    read(K);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u), read(v);
        adj.add(u, v);
    }
    tj.getg2();
    toposort();
    t.getrt();
    t.dfs1(t.rt, 0);
    t.dfs2(t.rt, t.rt);
    while (q--) {
        sol.solve();
    }
    return 0;
}
