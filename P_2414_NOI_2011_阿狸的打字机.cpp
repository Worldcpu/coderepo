#include<bits/stdc++.h>
using namespace std;
constexpr int MN=8e5+15;
struct Query{ int x,y,id; } qry[MN];
int n, siz[MN], dfn[MN], ans[MN],stk[MN], dtot;
string st;
vector<int> ft[MN];

struct BIT {
    int t[MN];
    int lowbit(int x) { return x&-x; }
    int query(int x) {
        int ret=0;
        while(x>0) ret+=t[x], x-=lowbit(x);
        return ret;
    }
    void update(int x, int k) {
        while(x<MN) t[x]+=k, x+=lowbit(x);
    }
} bit;

namespace ACAuto {
    struct Node { int ch[26], fail; } t[MN];
    int tot, g_top, ctot, cut[MN], sta[MN];

    void buildAC(string str) {
        int p = 0;
        g_top = 0;
        for (int i=0; i<str.length(); i++) {
            if (str[i]>='a' && str[i]<='z') {
                int ch = str[i]-'a';
                if (!t[p].ch[ch]) t[p].ch[ch] = ++tot;
                p = t[p].ch[ch];
                sta[++g_top] = p;
            } else if (str[i]=='B') {
                p = sta[--g_top];
            } else {
                cut[++ctot] = p;
            }
        }
    }

    void build() {
        queue<int> q;
        for (int i=0; i<26; i++) {
            if (t[0].ch[i]) {
                q.push(t[0].ch[i]);
                ft[0].push_back(t[0].ch[i]);
            }
        }
        while (!q.empty()) {
            int f = q.front(); q.pop();
            for (int i=0; i<26; i++) {
                int &v = t[f].ch[i];
                if (v) {
                    t[v].fail = t[t[f].fail].ch[i];
                    ft[t[v].fail].push_back(v);
                    q.push(v);
                } else {
                    v = t[t[f].fail].ch[i];
                }
            }
        }
    }
}
using namespace ACAuto;

bool cmp(Query x, Query y) {
    return x.y != y.y ? x.y < y.y : x.id < y.id;
}

void dfs(int u) {
    dfn[u] = ++dtot;
    siz[u] = 1;
    for (int v : ft[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
}

int main() {
    cin >> st;
    cin >> n;
    for (int i=1; i<=n; i++) {
        cin >> qry[i].x >> qry[i].y;
        qry[i].id = i;
    }
    sort(qry+1, qry+n+1, cmp);

    buildAC(st);
    build();
    dfs(0);

    for (int i=1, p=0, top=0, pt=0, up=0; i<=n; i++) {
        while (up < qry[i].y) {
            if (st[pt]>='a' && st[pt]<='z') {
                int ch = st[pt]-'a';
                p = t[p].ch[ch];
                stk[++top] = p;
                bit.update(dfn[p], 1);
            } else if (st[pt]=='B') {
                bit.update(dfn[p], -1);
                p = stk[--top];
            } else {
                up++;
            }
            pt++;
        }
        int node = cut[qry[i].x];
        ans[qry[i].id] = bit.query(dfn[node]+siz[node]-1) 
                         - bit.query(dfn[node]-1);
    }

    for (int i=1; i<=n; i++) 
        cout << ans[i] << '\n';
    return 0;
}
