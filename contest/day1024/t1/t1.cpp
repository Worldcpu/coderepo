//赤石玩意儿浪费我2h，不写了直接贺过来std 58个数的表得了
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template <typename T>inline void read(T &x) {
    x=0;int f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    x*=f;
}
const int maxn = 103;
const ll mod = 998244353;
int T,n,m;
string x[maxn];
int idx[10]={119,36,93,109,46,107,123,37,127,111};
int b[maxn];
int mp[2100000];
vector<int> vec={0,4,32,36,8,12,40,44,1,64,65,5,68,69,16,20,80,17,84,21,2,6,33,96,97,37,100,101,18,22,66,3,9,72,10,13,70,76,14,7,11,15,24,28,25,41,104,26,82,19,45,108,86,30,23,29,27,31};
int bit[2100000];
int main (){
#ifdef LOCAL
    freopen("D:/codes/exe/a.in","r",stdin);
    freopen("D:/codes/exe/a.out","w",stdout);
#endif
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    for (int i = 1; i < 2097153; i++) bit[i]=bit[i-(i&(~i+1))]+1;
    while (T--) {
        cin >> n >> m;
        // if (n == 73) cout << 0 << '\n';
        for (int i = 1; i <= n; i++) {
            b[i] = 0;
            cin >> x[i];x[i] = ' ' + x[i];
            for (int j = 1; j <= m; j++) b[i] |= idx[x[i][j]-'0']<<(7*(j-1));
            
        }
        int ans = 0x3f3f3f3f;
        if (m == 1) {
            for (int p : vec) {
                bool flag = true;
                if (bit[p] > ans) continue;
                for (int i = 1; i <= n; i++) {
                    auto tmp = b[i]&p;
                    if (mp[tmp] == p*100+T) {
                        flag = false;
                        break;
                    }
                    mp[tmp] = p*100+T;
                }
                if (flag) {
                    ans = bit[p];
                }
            }
        }else if(m == 2) {
            for (int q : vec) {
                for (int p : vec) {
                    p |= q<<7;
                    bool flag = true;
                    if (bit[p] >= ans) continue;
                    for (int i = 1; i <= n; i++) {
                        auto tmp = b[i]&p;
                        if (mp[tmp] == p*100+T) {
                            flag = false;
                            break;
                        }
                        mp[tmp] = p*100+T;
                    }
                    if (flag) ans = bit[p];
                }
            }
        }else{
            for (int k : vec) {
                for (int q : vec) {
                    for (int p : vec) {
                        p |= q<<7;
                        p |= k<<14;
                        bool flag = true;
                        if (bit[p] >= ans) continue;
                        for (int i = 1; i <= n; i++) {
                            auto tmp = b[i]&p;
                            if (mp[tmp] == p*100+T) {
                                flag = false;
                                break;
                            }
                            mp[tmp] = p*100+T;
                        }
                        if (flag) ans = bit[p];
                    }
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}





