#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int ML=19,mod=1e9+7,MZ=9*18+5;
int K,pw10[ML];

namespace DP{
    int a[ML],f[ML][MZ];
    int dfs(int pos,bool limit,int sum){
        if(!pos){
            return sum;
        }
        if(!limit && ~f[pos][sum]){
            return f[pos][sum];
        }
        int up = limit ? a[pos] : 9;
        int ret=0;
        for(int i=0;i<=up;i++){
            ret += dfs(pos-1, limit && i==up, sum+i);
        }
        if(!limit) f[pos][sum] = ret;
        return ret;
    }

    int solve(int x){
        int len=0;
        while(x>0){
            a[++len] = x%10;
            x/=10;
        }
        return dfs(len, true, 0);
    }

    void init(){
        memset(f,-1,sizeof(f));
    }
}

namespace Getup {
    pair<int,int> sol() {
        int sum = 0;
        int len = 1;
        int count = 9;
        while(K > sum + count * len) {
            sum += count * len;
            len++;
            count *= 10;
        }
        int offset = K - sum - 1;
        int num = pw10[len-1]+ offset / len;
        int remain = offset % len;
        return {num, remain};
    }
}

int work(int x,int k){
    int res=0;
    string s = to_string(x);
    for(int i=0;i<=k;i++) res += s[i]-'0';
    return res;
}

void initpw(){
    pw10[0]=1;
    for(int i=1;i<ML;i++) pw10[i]=pw10[i-1]*10;
    DP::init();
}

void solve(){
    cin>>K;
    auto [num,remain]=Getup::sol();
    int res=DP::solve(num - 1);
    res += work(num, remain);
    cout<<res<<'\n';
}

signed main(){
    initpw();
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
