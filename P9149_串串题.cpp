#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=1e9+7;
int T,n,m,w,d,ans,a[MN],b[MN],nxt[MN],tot,c[MN],cnt[MN],pw[MN],inv[MN],acnt;
bool vis[MN];

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
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b||b<0||a<0) return 0;
    else return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initnxt(){
    memset(nxt,0,sizeof(nxt));
    for(int i=2,j=0;i<=m;i++){
        while(j>0&&b[i]!=b[j+1]) j=nxt[j];
        if(b[i]==b[j+1]) j++;
        nxt[i]=j;
    }
}

void clear(){
    acnt=ans=tot=0;
    memset(cnt,0,sizeof(cnt));
    memset(vis,0,sizeof(vis));
    a[n+1]=b[m+1]=0;
}

void solve(){
    cin>>n>>m>>w>>d;
    clear();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
        vis[b[i]]=1;
    }
    for(int i=1;i<=w;i++){
        if(!vis[i]) acnt++;
    }
    initnxt();
    for(int i=1;i<=n;i++){
        if(vis[a[i]]) c[++tot]=i;
    }
    int l=1,r=0,ret=0;
    for(int i=1,j=0;i<=tot;i++){
        while(r<c[i]){
            r++;
            if(!vis[a[r]]){
                cnt[a[r]]++;
                if(cnt[a[r]]==1){
                    ret++;    
                }
            }
        }
        if(i>=m){
            while(l<c[i-m+1]){
                if(!vis[a[l]]){
                    cnt[a[l]]--;
                    if(cnt[a[l]]==0){
                        ret--;
                    }
                }
                l++;
            }
        }
        while(j>0&&a[c[i]]!=b[j+1]) j=nxt[j];
        if(a[c[i]]==b[j+1]){
            j++;
        }
        if(j==m){
            (ans+=getC(acnt-ret,d-ret))%=MOD;
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    initpw();
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
