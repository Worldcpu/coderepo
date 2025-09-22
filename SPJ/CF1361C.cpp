#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int beauty(int u, int v) {
    if (u == v) return 20;
    int x = u ^ v;
    int k = 0;
    while ((x & 1) == 0) x >>= 1, k++;
    return k;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<pair<int,int>> beads(n+1);
    for (int i = 1; i <= n; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        beads[i] = {a,b};
    }

    int jury_val = ouf.readInt();
    vector<int> jury_seq(2*n);
    for (int i = 0; i < 2*n; i++) {
        jury_seq[i] = ouf.readInt();
    }

    int user_val = ans.readInt();
    vector<int> user_seq(2*n);
    for (int i = 0; i < 2*n; i++) {
        user_seq[i] = ans.readInt();
    }

    // 验证序列合法性
    vector<int> pos(2*n+1,0);
    for (int i = 0; i < 2*n; i++) {
        if (user_seq[i] < 1 || user_seq[i] > 2*n)
            quitf(_wa, "pearl number %d out of range", user_seq[i]);
        pos[user_seq[i]]++;
    }
    for (int i = 1; i <= 2*n; i++)
        if (pos[i] != 1)
            quitf(_wa, "pearl %d appears %d times", i, pos[i]);

    // 检查每个配件的两颗珠子是否相邻
    for (int i = 1; i <= n; i++) {
        int u = 2*i-1, v = 2*i;
        int idx_u = find(user_seq.begin(), user_seq.end(), u) - user_seq.begin();
        int idx_v = find(user_seq.begin(), user_seq.end(), v) - user_seq.begin();
        if ((idx_u + 1) % (2*n) != idx_v && (idx_v + 1) % (2*n) != idx_u)
            quitf(_wa, "beads %d and %d of same accessory are not adjacent", u, v);
    }

    // 计算环的美丽值
    int min_beauty = 20;
    for (int i = 0; i < 2*n; i++) {
        int u_idx = user_seq[i]-1, v_idx = user_seq[(i+1)%(2*n)]-1;
        int u_val, v_val;
        if (u_idx % 2 == 0) u_val = beads[u_idx/2+1].first;
        else u_val = beads[u_idx/2+1].second;
        if (v_idx % 2 == 0) v_val = beads[v_idx/2+1].first;
        else v_val = beads[v_idx/2+1].second;
        min_beauty = min(min_beauty, beauty(u_val, v_val));
    }

    if (min_beauty != user_val)
        quitf(_wa, "declared beauty %d, actual beauty %d", user_val, min_beauty);

    quitf(_ok, "correct");
}
