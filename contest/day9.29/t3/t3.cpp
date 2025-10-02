#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,MV=1<<20;
int pre[MN],n,rt[MN],rtot,ans,cnt[MN];

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

bool merge(int &x, int y){
    if(!y)return 0;
    if(!x)return x=y,1;
    x = root(x), y = root(y);
    if(x == y)return 0;
    return pre[y]=x,1;
}

int lowbit(int x){
    return x&(-x);
}

void init(){
    memset(cnt,0,sizeof(cnt));
    rtot=ans=0;
}

void solve(){
    read(n);
    init();
    for(int i=1;i<=n;i++){
        int x;
        read(x);
        cnt[x]++;
        pre[i]=i;
    }
    for(int i=0;i<MV;i++){
        if(cnt[i]) rt[i]=++rtot;
        else rt[i]=0;
        int tmp=cnt[i];
        for(int j=i;j;j^=lowbit(j)){
            tmp+=merge(rt[i],rt[i^lowbit(j)]);
        }
        ans+=max(0ll,tmp-1)*i;
    }
    put(ans);
}

signed main(){
    #ifndef CPH
    freopen("mst.in","r",stdin);
    freopen("mst.out","w",stdout);
    #endif
    int qwq,T;
    read(qwq,T);
    while(T--){
        solve();
    }

    return 0;
}