#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=(1<<16),MOD=1e9+7;
int n,K,f[2][MN][3],ans[MN],nxt[MN][26],tmp1[MN],tmp2[MN];
string s;

int encode(int a[]){
    int ret=0;
    for(int i=0;i<K;i++){
        ret|=(a[i+1]-a[i])<<i;
    }
    return ret;
}

void decode(int hsh,int a[]){
    for(int i=0;i<K;i++){
        a[i+1]=(hsh>>i)&1;
    }
    for(int i=1;i<=K;i++) a[i]+=a[i-1];
}

int LCS(int x,char ch){
    decode(x,tmp1);
    for(int i=1;i<=K;i++){
        tmp2[i]=max({tmp2[i-1],tmp1[i],tmp1[i-1]+(ch==s[i])});
    }
    return encode(tmp2);
}

signed main(){
    cin>>n>>K>>s;
    s=" "+s;
    for(int i=0;i<(1<<K);i++){
        nxt[i]['N'-65]=LCS(i,'N');
        nxt[i]['O'-65]=LCS(i,'O');
        nxt[i]['I'-65]=LCS(i,'I');
    }
    f[0][0][0]=1;
    for(int i=1,now,lst;i<=n;i++){
        now=i&1,lst=!now;
        for(int j=0;j<(1<<K);j++){
            f[now][j][0]=f[now][j][1]=f[now][j][2]=0;
        }
        for(int j=0;j<(1<<K);j++){
            ((f[now][nxt[j]['N'-65]][1])+=f[lst][j][0]+f[lst][j][1]+f[lst][j][2])%=MOD;
            ((f[now][nxt[j]['O'-65]][0])+=f[lst][j][0]+f[lst][j][2])%=MOD;
            ((f[now][nxt[j]['O'-65]][2])+=f[lst][j][1])%=MOD;
            ((f[now][nxt[j]['I'-65]][0])+=f[lst][j][0]+f[lst][j][1])%=MOD;
        }
    }
    for(int i=0;i<(1<<K);i++){
        (ans[__builtin_popcount(i)]+=f[n&1][i][0]+f[n&1][i][1]+f[n&1][i][2])%=MOD;
    }
    for(int i=0;i<=K;i++) cout<<ans[i]<<'\n';
    return 0;
}
