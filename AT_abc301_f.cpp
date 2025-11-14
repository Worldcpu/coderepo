#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,pw[MN],inv[MN],pw26[MN],cntq,cntd,f[MN],g[MN],h[MN];
string st;
unordered_map<char,bool> vis;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    pw26[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD,pw26[i]=pw26[i-1]*26%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int getA(int a,int b){
    return getC(a,b)*pw[b]%MOD;
}

signed main(){
    initpw();
    cin>>st;
    n=st.length();
    st=" "+st;
    cntd=26;
    f[0]=g[0]=h[0]=1;
    for(int i=1,t=1;i<=n;i++){
        if(st[i]=='?'){
            cntq++;
            for(int j=0;j<=min(cntq,cntd);j++){
                f[i]=(f[i]+t*getC(cntq,j)*getA(cntd,j)%MOD*pw26[cntq-j]%MOD)%MOD;
            }
            g[i]=(g[i-1]+f[i-1])*26%MOD;
            h[i]=(h[i-1]+g[i-1])*26%MOD; 
        }else{
            if(st[i]>='A'&&st[i]<='Z'){
                if(vis[st[i]]) t=0;
                else{
                    vis[st[i]]=1;
                    cntd--;
                }
            }
            for(int j=0;j<=min(cntq,cntd);j++){
                f[i]=(f[i]+t*getC(cntq,j)*getA(cntd,j)%MOD*pw26[cntq-j]%MOD)%MOD;
            }
            if(st[i]>='A'&&st[i]<='Z'){ 
                g[i]=h[i]=g[i-1];
            }else{
                g[i]=f[i-1];
                h[i]=h[i-1];
            }
        }
    }
    cout<<h[n];
    return 0;
}
