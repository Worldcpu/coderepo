#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN = 1000000 + 15;
const int N = 1000000; 

int T, mu[MN], d[MN],g[MN], ans[MN];
pir pr[MN];
static bool mark[MN];

struct BIT{
    int t[MN];
    int lowbit(int x){ return x & -x; }
    void modify(int x,int k){
        while(x < MN){
            t[x] += k;
            x += lowbit(x);
        }
    }
    int query(int x){
        int ret = 0;
        while(x){
            ret += t[x];
            x -= lowbit(x);
        }
        return ret;
    }
} bit;

struct Query{
    int n,m,a,id;
    int solve(){
        if(n>m) swap(n,m);
        int ret=0;
        for(int l=1,r; l<=n; l=r+1){
            r = min(n/(n/l), m/(m/l));
            ret += (bit.query(r) - bit.query(l-1)) * (n/l) * (m/l);
        }
        return ret;
    }
} q[MN];

void euler(int n){
    mu[1] = 1;
    d[1] = 1;
    vector<int> p;

    for(int i = 2; i <= n; i++){
        if(!mark[i]){
            p.push_back(i);
            mu[i] = -1;
            d[i] = i + 1;
            g[i]=i+1;
        }
        for(size_t j = 0; j < p.size() && i * p[j] <= n; j++){
            int tmp = i * p[j];
            mark[tmp] = true;
            if(i % p[j] == 0){
                mu[tmp] = 0;
                g[tmp] = g[i] * p[j] + 1;
                d[tmp]=d[i]/g[i]*g[tmp];
                break;
            } else {
                mu[tmp] = -mu[i];
                g[tmp]=p[j]+1;
                d[tmp] = d[i] * d[p[j]];
            }
        }
    }
    for(int i = 1; i <= n; i++) pr[i] = pir(d[i], i);
    sort(pr + 1, pr + 1 + n); 
}

bool cmp(const Query &x,const Query &y){ return x.a < y.a; }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    euler(N);
    cin >> T;
    for(int i=1;i<=T;i++){
        cin >> q[i].n >> q[i].m >> q[i].a;
        q[i].id = i;
    }
    sort(q+1, q+1+T, cmp);

    for(int i=1, it=1; i<=T; i++){
        while(it <= N && pr[it].first <= q[i].a){
            int dval = pr[it].second;
            int s = pr[it].first;
            for(int j = dval; j <= N; j += dval){
                bit.modify(j, s * mu[j / dval]);
            }
            it++;
        }
        ans[q[i].id] = q[i].solve();
    }

    for(int i=1;i<=T;i++){
        cout << (ans[i]&(~(1<<31))) << '\n';
    }
    return 0;
}
