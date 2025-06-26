#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15;
int nxt[MN][26],g[MN],f[MN],n,ans;
string s;

signed main(){
    cin>>n>>s;
    s=" "+s;
    for(int i=1;i<=n;i++){
        g[i]=i;
        int x=nxt[g[i-1]][s[i]-'a'];
        if(x) g[i]=g[x-1],f[i]=f[x-1]+1;
        nxt[g[i]][s[i]-'a']=i;
        ans+=f[i];
    }
    cout<<ans;
    return 0;
}
