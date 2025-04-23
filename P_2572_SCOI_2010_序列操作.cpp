#include <bits/stdc++.h>
using namespace std;
//要开始屎山了
//加油吧starlinkOvO
//(OvO----)=33
const int MN = 2e5 + 3;
int a[MN], n, m;
int op, x, y;

struct starlink{
    int l, r;
    //左边界; 右边界
    int v, fl, ovo;
    //v: 值, 同时也表示区间1的个数
    //fl = -1 无状态; fl = 0 区间转为0; fl = 1 区间转为1;
    //ovo: 是否翻转
    int maxx[2], lmax[2], rmax[2];
    //区间最长, 左端点最长, 右端点最长
};
starlink tree[MN << 2];

void pushup(int k){
    tree[k].v = tree[k << 1].v + tree[k << 1| 1].v;

    for (int i = 0; i <= 1; i++) {
        tree[k].lmax[i] = tree[k << 1].lmax[i];
        if (i == 1 && tree[k << 1].v == tree[k << 1].r - tree[k << 1].l + 1)
            tree[k].lmax[i] += tree[k << 1| 1].lmax[i];
        else if (i == 0 && tree[k << 1].v == 0)
            tree[k].lmax[i] += tree[k << 1| 1].lmax[i];

        tree[k].rmax[i] = tree[k << 1| 1].rmax[i];
        if (i == 1 && tree[k << 1| 1].v == tree[k << 1| 1].r - tree[k << 1| 1].l + 1)
            tree[k].rmax[i] += tree[k << 1].rmax[i];
        else if (i == 0 && tree[k << 1| 1].v == 0)
            tree[k].rmax[i] += tree[k << 1].rmax[i];

        tree[k].maxx[i] = tree[k << 1].rmax[i] + tree[k << 1| 1].lmax[i];
        tree[k].maxx[i] = max(tree[k].maxx[i], tree[k << 1].lmax[i]);
        tree[k].maxx[i] = max(tree[k].maxx[i], tree[k << 1| 1].rmax[i]);
    }
}
void pushdown(int k){
    if (tree[k].fl != -1) {
        tree[k].ovo = 0;
        int val = tree[k].fl;
        tree[k << 1].v = (tree[k << 1].r - tree[k << 1].l + 1) * val;
        tree[k << 1| 1].v = (tree[k << 1| 1].r - tree[k << 1| 1].l + 1) * val;

        tree[k << 1].fl = tree[k << 1| 1].fl = val;
        tree[k << 1].ovo = tree[k << 1| 1].ovo = 0;

        tree[k << 1].maxx[val] = tree[k << 1].lmax[val] = tree[k << 1].rmax[val] = tree[k << 1].r - tree[k << 1].l + 1;
        tree[k << 1].maxx[val ^ 1] = tree[k << 1].lmax[val ^ 1] = tree[k << 1].rmax[val ^ 1] = 0;

        tree[k << 1| 1].maxx[val] = tree[k << 1| 1].lmax[val] = tree[k << 1| 1].rmax[val] = tree[k << 1| 1].r - tree[k << 1| 1].l + 1;
        tree[k << 1| 1].maxx[val ^ 1] = tree[k << 1| 1].lmax[val ^ 1] = tree[k << 1| 1].rmax[val ^ 1] = 0;

        tree[k].fl = -1;
    }

    if (tree[k].ovo) {
        tree[k << 1].v = (tree[k << 1].r - tree[k << 1].l + 1) - tree[k << 1].v;
        tree[k << 1| 1].v = (tree[k << 1| 1].r - tree[k << 1| 1].l + 1) - tree[k << 1| 1].v;

        if (tree[k << 1].fl != -1) tree[k << 1].fl ^= 1;
        else tree[k << 1].ovo ^= 1;
        if (tree[k << 1| 1].fl != -1) tree[k << 1| 1].fl ^= 1;
        else tree[k << 1| 1].ovo ^= 1;

        swap(tree[k << 1].maxx[0], tree[k << 1].maxx[1]);
        swap(tree[k << 1].lmax[0], tree[k << 1].lmax[1]);
        swap(tree[k << 1].rmax[0], tree[k << 1].rmax[1]);

        swap(tree[k << 1| 1].maxx[0], tree[k << 1| 1].maxx[1]);
        swap(tree[k << 1| 1].lmax[0], tree[k << 1| 1].lmax[1]);
        swap(tree[k << 1| 1].rmax[0], tree[k << 1| 1].rmax[1]);

        tree[k].ovo = 0;
    }
}

void build(int l, int r, int k){
    tree[k].l = l, tree[k].r = r, tree[k].fl = -1;
    if (l == r) {
        tree[k].v = a[l];
        tree[k].maxx[0] = tree[k].lmax[0] = tree[k].rmax[0] = a[l] == 0;
        tree[k].maxx[1] = tree[k].lmax[1] = tree[k].rmax[1] = a[l] == 1;
        return ;
    }

    int mid = (tree[k].l + tree[k].r) >> 1;
    build(l, mid, k << 1); 
    build(mid + 1, r, k << 1| 1);
    pushup(k);
}

void updadd(int l, int r, int k){
    pushdown(k);

    if (tree[k].l >= l && tree[k].r <= r){
        tree[k].v = (r - l + 1) * op;
        tree[k].fl = op;
        tree[k].maxx[op] = tree[k].lmax[op] = tree[k].rmax[op] = r - l + 1;
        tree[k].maxx[op ^ 1] = tree[k].lmax[op ^ 1] = tree[k].rmax[op ^ 1] = 0;
        return ;
    }

    int mid = (tree[k].l + tree[k].r) >> 1;
    if (mid < l) updadd(l, r, k << 1| 1);
    else if (mid >= r) updadd(l, r, k << 1);
    else updadd(l, r, k << 1), updadd(l, r, k << 1| 1);
    pushup(k);
}
void updchg(int l, int r, int k){
    pushdown(k);

    if (tree[k].l >= l && tree[k].r <= r){
        tree[k].v = (r - l + 1) - tree[k].v;
        tree[k].ovo ^= 1;

        //取反了就全反过来潵
        swap(tree[k].maxx[0], tree[k].maxx[1]);
        swap(tree[k].lmax[0], tree[k].lmax[1]);
        swap(tree[k].rmax[0], tree[k].rmax[1]);

        return ;
    }

    int mid = (tree[k].l + tree[k].r) >> 1;
    if (mid < l) updchg(l, r, k << 1| 1);
    else if (mid >= r) updchg(l, r, k << 1);
    else updchg(l, r, k << 1), updchg(l, r, k << 1| 1);
    pushup(k);
}

int query(int l, int r, int k){
    pushdown(k);

    if (tree[k].l >= l && tree[k].r <= r) return tree[k].v;

    int mid = (tree[k].l + tree[k].r) >> 1;
    if (mid < l) return query(l, r, k << 1| 1);
    else if (mid >= r) return query(l, r, k << 1);
    else return query(l, r, k << 1) + query(l, r, k << 1| 1);
}
starlink sumqy(int l, int r, int k){
    pushdown(k);

    if (tree[k].l >= l && tree[k].r <= r) return tree[k];

    int mid = (tree[k].l + tree[k].r) >> 1;
    if (mid < l) return sumqy(l, r, k << 1| 1);
    else if (mid >= r) return sumqy(l, r, k << 1);
    else {
        starlink t, ll = sumqy(l, mid, k << 1), rr = sumqy(mid + 1, r, k << 1| 1);
        t.l = l, t.r = r;
        t.v = ll.v + rr.v;

        for (int i = 0; i <= 1; i++) {

            t.lmax[i] = ll.lmax[i]; //左
            if (i == 1 && ll.v == ll.r - ll.l + 1) t.lmax[i] += rr.lmax[i]; //1满
            else if (i == 0 && ll.v == 0) t.lmax[i] += rr.lmax[i]; //0满

            t.rmax[i] = rr.rmax[i]; //右 
            if (i == 1 && rr.v == rr.r - rr.l + 1) t.rmax[i] += ll.rmax[i]; //1满 
            else if (i == 0 && rr.v == 0) t.rmax[i] += ll.rmax[i]; //0满 

            t.maxx[i] = ll.rmax[i] + rr.lmax[i];
            t.maxx[i] = max(t.maxx[i], ll.lmax[i]);
            t.maxx[i] = max(t.maxx[i], rr.rmax[i]);
        }
        return t;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, n, 1);

    for (int i = 1; i <= m; i++) {
        cin >> op >> x >> y;

        if (op == 0 || op == 1) updadd(x, y, 1); //区间修改为0或1
        else if (op == 2) updchg(x, y, 1); //区间取反
        else if (op == 3) cout << query(x, y, 1) << endl; //求区间内1的个数
        else if (op == 4) cout << sumqy(x, y, 1).maxx[1] << endl; //求区间内最长的1序列
    }

    return 0;
}