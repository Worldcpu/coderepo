#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int num[MN],c[MN],cnt,tot,a,b,ans;

void dfs(int x){
    if(x>b) return;
    num[++tot]=x;
    dfs(x*10+6);
    dfs(x*10+8);
}

void clac(int x,int pos,int op){
    ans+=(b/x-(a-1)/x)*op;
    for(int i=pos+1;i<=cnt;i++){
        if(1.0*x/__gcd(x,c[i])*c[i]<=b){
            clac(1.0*x/__gcd(x,c[i])*c[i],i,-op);
        }
    }
}

signed main(){
    cin>>a>>b;
    dfs(0);
    sort(num+1,num+1+tot);
    for(int i=1;i<=tot;i++){
        if(!num[i]) continue;
        for(int j=i+1;j<=tot;j++){
            if(num[j]%num[i]==0){
                num[j]=0;
            }
        }
    }
    for(int i=1;i<=tot;i++){
        if(num[i]) c[++cnt]=num[i];
    }
    reverse(c+1,c+1+cnt);
    clac(1,0,1);
    cout<<b-a+1-ans;
    return 0;
}
