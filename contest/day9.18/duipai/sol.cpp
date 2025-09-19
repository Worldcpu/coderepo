#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int r,c;
    if(!(cin>>n>>r>>c)) return 0;
    vector<int> x(n), y(n);
    vector<ll> a(n);
    for(int i=0;i<n;i++){
        cin>>x[i]>>y[i]>>a[i];
    }
    ll ans = 0;
    int LIM = 1<<n;
    // 枚举第一轮选中的物品子集 mask
    for(int mask=0; mask < LIM; ++mask){
        // 检查第一轮是否满足每行最多一个
        // 用 unordered_set 记录已用的行（n 小，开销可以接受）
        bool ok = true;
        unordered_set<int> usedRow;
        usedRow.reserve(32);
        for(int i=0;i<n;i++){
            if(mask & (1<<i)){
                if(usedRow.find(x[i]) != usedRow.end()){
                    ok = false;
                    break;
                }
                usedRow.insert(x[i]);
            }
        }
        if(!ok) continue;
        // 计算第一轮之和
        ll sum1 = 0;
        for(int i=0;i<n;i++) if(mask & (1<<i)) sum1 += a[i];

        // 第二轮：在未被第一轮选中的物品中，每列取一个最大值
        unordered_map<int,ll> colMax; // col -> max value among items not in mask
        colMax.reserve(32);
        for(int i=0;i<n;i++){
            if(mask & (1<<i)) continue; // 被第一轮选中的不能再选
            auto it = colMax.find(y[i]);
            if(it == colMax.end()) colMax[y[i]] = a[i];
            else if(a[i] > it->second) it->second = a[i];
        }
        ll sum2 = 0;
        for(auto &kv : colMax) sum2 += kv.second;
        ans = max(ans, sum1 + sum2);
    }

    cout<<ans<<"\n";
    return 0;
}
