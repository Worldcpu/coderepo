#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int n,f[MN][MN],nxt[MN],tot;
char c[MN];
string s;

void getnxt(){
    nxt[1]=0;
    for(int i=2,j=0;i<=tot;i++){
        while(j>0&&c[i]!=c[j+1]) j=nxt[j];
        if(c[i]==c[j+1]) j++;
        nxt[i]=j;
    }
}

int check(int l,int r){
    tot=0;
    for(int i=l;i<=r;i++){
        c[++tot]=s[i];
    }
    getnxt();
    if(tot%(tot-nxt[tot])==0) return tot-nxt[tot];
    else return -1;
}

void solve(){
    n=s.length();
    s=" "+s;
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) f[i][i]=1;
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            int ret=check(l,r);
            if(ret!=-1) f[l][r]=f[l][l+ret-1];
            for(int k=l;k<r;k++){
                f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
            }
        }
    }
    cout<<f[1][n]<<'\n';
}

signed main(){
    while(cin>>s){
        if(s=="*") break;
        solve();
    }
    return 0;
}
