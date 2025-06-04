#include<map>
#include<set>
#include<cmath>
#include<cstdio>
#include<stack>
#include<vector>
#include<queue>
#include<cstring>
#include<string>
#include<sstream>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
constexpr int MN=1e4+15,MP=65;
int T,n,q,cnt;

struct xxj{
    int p[MP], c[MP], size, totc;
    bool flag = 0;

    void clear(){
        flag = totc = 0;
        memset(p, 0, sizeof(p));
        memset(c, 0, sizeof(c));
    }

    void insert(int x){
        for(int i = 63; i >= 0; i--){
            if((x >> i) & 1){
                if(!p[i]){
                    p[i] = x;
                    size++;
                    return;
                }
                x ^= p[i];
            }
        }
        flag = 1;
    }

    void getc(){
        // 复制并简化基向量
        for(int i = 63; i >= 0; i--) c[i] = p[i];
        for(int i = 63; i >= 0; i--){
            if(!c[i]) continue;
            for(int j = i - 1; j >= 0; j--){
                if((c[i] >> j) & 1) c[i] ^= c[j];
            }
        }
        // 收集非零基向量并按位权排序
        int tmp[MP], cnt = 0;
        for(int i = 0; i <= 63; i++) {
            if(c[i]) tmp[cnt++] = c[i];
        }
        totc = cnt;
        // 连续存储到c[0..totc-1]
        for(int i = 0; i < cnt; i++) {
            c[i] = tmp[i];
        }
    }

    int query(int k){
        if(flag) k--;     // 线性相关时0为第1小
        if(k == 0) return 0;
        if(k >= (1LL << totc)) return -1;  // k超出范围
        int ans = 0;
        // 按基向量顺序（位权从低到高）处理k的每一位
        for(int i = 0; i < totc; i++){
            if(k & (1LL << i)) ans ^= c[i];  // 第i位对应第i个基向量
        }
        return ans;
    }
}xj;

void solve(){
    xj.clear();
    cout<<"Case #"<<++cnt<<": \n";
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        xj.insert(x);
    }
    xj.getc();
    cin>>q;
    while(q--){
        int k;
        cin>>k;
        cout<<xj.query(k)<<'\n';
    }
}

signed main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
