#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e4+15;
int f[122][MN],l,r,tot,K,a[122];

int dfs(int pos,bool lim,int sum,int to){
    if(!pos) return max(sum,0ll);
    if(!lim&&~f[pos][sum]) return f[pos][sum];
    int up,ret=0;
    if(lim) up=a[pos];
    else up=K-1;
    for(int i=0;i<=up;i++){
        if(to==0) ret+=dfs(pos-1,lim&&i==up,sum+i*(pos-1),to);
        else ret+=dfs(pos-1,lim&&i==up,sum+(pos>=to?i:-i),to);
    }
    if(!lim) f[pos][sum]=ret;
    return ret;
}

int solve(int x){
    tot=0;
    while(x){
        a[++tot]=x%K;
        x/=K;
    }
    memset(f,-1,sizeof(f));
    int ans=dfs(tot,1,0,0);
    for(int i=2;i<=tot;i++){
        memset(f,-1,sizeof(f));
        ans-=dfs(tot,1,0,i);
    }
    return ans;
}

signed main(){
    cin>>l>>r>>K;
    cout<<solve(r)-solve(l-1);
    return 0;
}
