#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e4+15;
int m,K,ans,f[15][MN][91],a[MN];

int dfs(int pos,bool lim,int s,int w){
    if(!pos) return s==w%K&&w;
    if(!lim&&~f[pos][s][w]) return f[pos][s][w];
    int up=(lim?a[pos]:9);
    int ret=0;
    for(int i=0;i<=up;i++){
        ret+=dfs(pos-1,lim&&i==up,(s*10+i)%K,w+i);
    }
    if(!lim) f[pos][s][w]=ret;
    return ret;
}

int solve(int x){
    int len=0;
    while(x>0){
        a[++len]=x%10;
        x/=10;
    }
    return dfs(len,1,0,0);
}


signed main(){
    cin>>K>>m;
    memset(f,-1,sizeof(f));
    if(K<=1e4){
        cout<<solve(m);
        return 0;
    }
    int ans=0;
    for(int i=0;i<=90;i++){
        for(int j=i;j<=m;j+=K){
            int sum=0,x=j;
            while(x){
                sum+=x%10;
                x/=10;
            }
            if(sum%K==i) ans++;
        }
    }
    cout<<ans-1;
    return 0;
}
