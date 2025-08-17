#include <bits/stdc++.h>
using namespace std;
constexpr int MN=15200;
constexpr int MX=MN*MN; // 差平方最大值
bitset<MX+5> vis;
int pre[MX+5];
int a,b;

void solve(){
    cin>>a>>b;
    int d=abs(a*a-b*b);
    cout<<pre[d]<<'\n';
}

int main(){
    for(int i=1;i<MN;i++){
        for(int j=i+1;j<MN;j++){
            vis[j*j-i*i]=1;
        }
    }
    for(int i=1;i<=MX;i++) pre[i]=pre[i-1]+vis[i]; // 前缀和
    cerr<<"qwq\n";
    int T;cin>>T;
    while(T--) solve();
}
