#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
constexpr int MN=2e7+15;
int a[MN],b[MN],ita[MN],itb[MN],n,m;
ll f[3],cur,ans;
ull _k1,_k2;

namespace Rand{
const int threshold=10000000;
ull k1,k2;

ull Rand(){
    ull k3=k1,k4=k2;
    k1=k4;
    k3^=(k3<<23);
    k2=k3^k4^(k3>>17)^(k4>>26);
    return k2+k4;
}

void gen(int n,ull _k1,ull _k2){
    k1=_k1,k2=_k2;
    for(int i=1;i<=n;i++){
        a[i]=Rand()%threshold+1;
        b[i]=Rand()%threshold+1+a[i];
    }
}
}

void init(){
    Rand::gen(n,_k1,_k2);
    memset(f,0,sizeof(f));
    ans=cur=0;
}

void solve(){
    init();
    sort(a+1,a+1+n,greater<int>());
    sort(b+1,b+1+n,greater<int>());
    ita[0]=itb[0]=1;
    for(int i=0;i<=m;i++){
        if(i+1<=m&&ita[i]<=n){
            int nxt=(cur+1)%3;
            if(f[cur]+a[ita[i]]>f[nxt]){
                f[nxt]=f[cur]+a[ita[i]];
                ita[i+1]=ita[i]+1;
                itb[i+1]=itb[i];
            }
        }
        if(i+2<=m&&itb[i]<=n){
            int nxt=(cur+2)%3;
            if(f[cur]+b[itb[i]]>f[nxt]){
                f[nxt]=f[cur]+b[itb[i]];
                ita[i+2]=ita[i];
                itb[i+2]=itb[i]+1;
            }
        }
        ans^=f[cur];
        cur=(cur+1)%3;
    }
    cout<<ans<<'\n';
}

int main(){
    while(cin>>n>>m>>_k1>>_k2){
        solve();
    }
}