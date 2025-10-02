#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=22,MOD=998244353;
int n,f[1<<MN];
bool vis[1<<MN];
string s;

int dfs(int st){
    if(!st) return 1;
    if(vis[st]) return f[st];
    vis[st]=1;
    int ret=0,pre=-1;
    for(int i=0;i<n;i++){
        if((st>>i)&1){
            if(pre==-1||s[i]!=s[pre]){
                ret+=dfs(st^(1<<i));
            }
            pre=i;
        }
    }
    return f[st]=ret%MOD;
}

signed main(){
    cin>>n>>s;
    cout<<dfs((1<<n)-1);

    return 0;
}