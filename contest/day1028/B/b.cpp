#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,INF=1e18;
int a[3][MN], n, m, pre[MN], ans1, ans2;

struct Segment {
    #define ls p<<1
    #define rs p<<1|1
    struct Node {
        int l, r, val, add;
    } t[MN << 2];

    void pushup(int p) { t[p].val = max(t[ls].val, t[rs].val); }

    void doadd(int p, int k) {
        t[p].val += k;
        t[p].add += k;
    }

    void build(int p, int l, int r) {
        t[p].l = l; t[p].r = r; t[p].add = 0;
        if (l == r) { t[p].val = 0; return; }
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(p);
    }

    void pushdown(int p) {
        if (t[p].add) {
            doadd(ls, t[p].add);
            doadd(rs, t[p].add);
            t[p].add = 0;
        }
    }

    int querymx(int p, int fl, int fr) {
        if (t[p].l >= fl && t[p].r <= fr) return t[p].val;
        pushdown(p);
        int mid = (t[p].l + t[p].r) >> 1, ret = -INF;
        if (fl <= mid) ret = max(ret, querymx(ls, fl, fr));
        if (fr > mid) ret = max(ret, querymx(rs, fl, fr));
        return ret;
    }

    void add(int p, int fl, int fr, int k) {
        if (t[p].l >= fl && t[p].r <= fr) { doadd(p, k); return; }
        pushdown(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (fl <= mid) add(ls, fl, fr, k);
        if (fr > mid) add(rs, fl, fr, k);
        pushup(p);
    }

    void setval(int p, int pos, int v) {
        if (t[p].l == t[p].r) {
            t[p].val = v;
            return;
        }
        pushdown(p);
        int mid = (t[p].l + t[p].r) >> 1;
        if (pos <= mid) setval(ls, pos, v);
        else setval(rs, pos, v);
        pushup(p);
    }
} sg;

void init() {
    ans1=ans2=0;
}


void solve() {
    cin >> n >> m;
    init();
    for(int i=1;i<=2;i++){
        for(int j=1;j<=n;j++){
            char x;
            cin>>x;
            a[i][j]=x-'0';
        }
    }
    sg.build(1,1,n);
    for(int i=1,cnt=0;i<=n;i++){
        if(a[1][i]==0 && a[2][i]==0) cnt--;
        else if(a[1][i]==1 && a[2][i]==1) cnt+=2;
        ans1=max(ans1,cnt);
        cnt=max(cnt,0ll);
    }

    for(int i=1,lst=-1;i<=n;i++){
        int now;
        if(a[1][i]==0&&a[2][i]==1) now=0;
        else if(a[1][i]==1&&a[2][i]==0) now=1;

        if(a[1][i]==0 && a[2][i]==0) sg.add(1,1,i,-1);
        else if(a[1][i]==1 && a[2][i]==1) sg.add(1,1,i,2),lst=-1; // 这里可以随便选择方向要注意
        else{
            if(lst==-1||lst==now) sg.add(1,1,i-1,1),lst=now; 
            else lst=-1; 
            // 好像必须要加这个玩意，断开后可以重新选择方向不然只能过特殊性质很难泵，考场上没有这个
            sg.setval(1,i,1);
        }
        ans2=max(ans2,sg.querymx(1,1,i));
    }
    ans2-=m*2;
    cout<<max(ans1,ans2)<<'\n';
}

signed main() {
    int subt, T;
    cin >> subt >> T;
    while(T--) solve();
    return 0;
}
