#include<bits/stdc++.h>
using namespace std;
constexpr int MN = 2e6 + 15;

struct Node {
    int x, y, op, id;
} q[MN], tmp[MN];
int ans[MN], tot;


struct BIT {
    int t[MN];

    int lowbit(int x) {
        return x & -x;
    }

    int query(int x) {
        int ret = 0;
        while (x) {
            ret += t[x];
            x -= lowbit(x);
        }
        return ret;
    }

    void update(int x, int k) {
        while (x <= MN) {
            t[x] += k;
            x += lowbit(x);
        }
    }
} bit;

bool cmp2(Node x, Node y) {
    if (x.x != y.x) return x.x < y.x;
    return x.y < y.y;
}

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    int i = l, j = mid + 1;
    sort(q + l, q + mid + 1, cmp2);
    sort(q + mid + 1, q + r + 1, cmp2);
    while (j <= r) {
        while (i <= mid && q[i].x <= q[j].x) {
            if (!q[i].id) bit.update(q[i].y, q[i].op);
            i++;
        }
        if (q[j].id) ans[q[j].id] += q[j].op * bit.query(q[j].y);
        j++;
    }
    for (int p = l; p < i; p++) {
        if (!q[p].id) bit.update(q[p].y, -q[p].op);
    }
}

bool cmp(Node x, Node y) {
    return x.id < y.id;
}

int main() {
    int op;
    while (1) {
        cin >> op;
        if (op == 3) break;
        if (op == 1) {
            int x, y, val;
            cin >> x >> y >> val;
            q[++tot] = {x, y, val, 0};
        } else if (op == 2) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int query_id = ++tot;
            q[tot] = {x2, y2, 1, query_id};
            q[++tot] = {x1 - 1, y2, -1, query_id};
            q[++tot] = {x2, y1 - 1, -1, query_id};
            q[++tot] = {x1 - 1, y1 - 1, 1, query_id};
        }
    }
    cdq(1, tot);
    sort(q + 1, q + tot + 1, cmp);
    int i = 1;
    // while (i <= tot) {
    //     if (q[i].id == 0) {
    //         i++;
    //         continue;
    //     }
    //     int current_id = q[i].id;
    //     vector<int> values;
    //     while (i <= tot && q[i].id == current_id) {
    //         values.push_back(ans[i]);
    //         i++;
    //     }
    //     if (values.size() == 4) {
    //         int a = values[0], b = values[1], c = values[2], d = values[3];
    //         cout << a - b - c + d << '\n';
    //     }
    // }
    for(int i=1;i<=tot;i++){
        if(q[i].id) cout<<ans[q[i].id]<<'\n';
        i+=3;
    }
    return 0;
}