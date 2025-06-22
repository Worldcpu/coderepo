#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1520,MM=(1<<16),MMM=150,MOD=1e9+7;
int T,n,m,f[2][MM],tmp1[MMM],tmp2[MMM],nxt[MM][26];
int ans[MN];
string s;

int encode(int a[]){
    int ret=0;
    for(int i=0;i<m;i++){
        ret|=(a[i+1]-a[i])<<i;
    }
    return ret;
}

void decode(int hsh,int a[]){
    for(int i=0;i<m;i++){
        a[i+1]=(hsh>>i)&1;
    }
    for(int i=1;i<=m;i++) a[i]+=a[i-1];
}

int LCS(int hsh,char ch){
    decode(hsh,tmp1);
    for(int i=1;i<=m;i++) tmp2[i]=max({tmp2[i-1],tmp1[i],tmp1[i-1]+(ch==s[i])});
    return encode(tmp2);
}

void init(){
    memset(ans,0,sizeof(ans));
    memset(f,0,sizeof(f));
    memset(nxt,0,sizeof(nxt));
}

void solve(){
    init();
    cin>>s>>n;
    m=s.length();
    s=' '+s;
    f[0][0]=1;
    for(int i=0;i<(1<<m);i++){
        nxt[i]['A'-65]=LCS(i,'A');
        nxt[i]['C'-65]=LCS(i,'C');
        nxt[i]['G'-65]=LCS(i,'G');
        nxt[i]['T'-65]=LCS(i,'T');
    }
    for(int i=1,now,lst;i<=n;i++){
        now=i&1,lst=!now;
        for(int j=0;j<(1<<m);j++) f[now][j]=0;
        for(int j=0;j<(1<<m);j++){
            (f[now][nxt[j]['A'-65]]+=f[lst][j])%=MOD;
            (f[now][nxt[j]['C'-65]]+=f[lst][j])%=MOD;
            (f[now][nxt[j]['G'-65]]+=f[lst][j])%=MOD;
            (f[now][nxt[j]['T'-65]]+=f[lst][j])%=MOD;
        }
    }
    for(int i=0;i<(1<<m);i++){
        (ans[__builtin_popcount(i)]+=f[n&1][i])%=MOD;
    }
    for(int i=0;i<=m;i++) cout<<ans[i]<<'\n';
}

signed main(){
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
