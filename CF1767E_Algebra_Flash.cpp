#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
using namespace __gnu_pbds;
using namespace std;
constexpr int MN=3e5+15;
int n,m,c[MN],x[MN],e[MN];
gp_hash_table<int,int> mp;

void add(int x,int y){
    e[x]|=(1ll<<(y-1));
    e[y]|=(1ll<<(x-1));
}

int lowbit(int x){
    return x&-x;
}

int dfs(int s){
    if(!s) return 0;
    if(mp.find(s)!=mp.end()) return mp[s];
    int p=__lg(lowbit(s))+1;
    int ret=dfs(s^(1ll<<(p-1)));
    if(!(e[p]>>(p-1)&1)) ret=max(ret,dfs(s^(1ll<<(p-1))^(s&e[p]))+x[p]);
    return mp[s]=ret;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    add(c[1],c[1]),add(c[n],c[n]);
    for(int i=2;i<=n;i++){
        add(c[i],c[i-1]);
    }
    int sum=0;
    for(int i=1;i<=m;i++){
        cin>>x[i];
        sum+=x[i];
    }
    cout<<sum-dfs((1ll<<m)-1);
    return 0;
}
