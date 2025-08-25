#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e6+15,MOD=998244353;
int n,ans,totr,pre[MN],lstp[MN],nxtp[MN],suf[MN],pos1[MN],pw2[MN],L[MN],R[MN];
string st;

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
    pw2[0]=1;
    for(int i=1;i<MN;i++) pw2[i]=pw2[i-1]*2%MOD;
}

signed main(){
    cin>>st;
    initpw();
    n=st.length();
    st=" "+st;
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]+(st[i]=='('?1:-1);
        L[i]=L[i-1]+(st[i]=='(');
        R[i]=R[i-1]+(st[i]==')');
        totr+=(st[i]==')');
    }
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1]+(st[i]==')'?1:-1);
    }
    for(int i=1,lst=0;i<=n;i++){
        if(pre[i]==1){
            lstp[i]=lst;
            lst=i;
        }
    }
    for(int i=n,lst=n+1;i>=1;i--){
        if(pre[i]==1){
            nxtp[i]=lst;
            lst=i;
        }
    }
    for(int i=1;i<=n;i++){
        if(pre[i]==1){
            int tmp=ksm(2,L[i])*ksm(2,R[n]-R[i])%MOD;
            ans=(ans+tmp)%MOD;
            if(i!=n){
                tmp=ksm(2,L[i])*ksm(2,R[n]-R[nxtp[i]])%MOD;
                ans=(ans-tmp+MOD)%MOD;
            }
        }
    }
    cout<<(ans*ksm(pw2[n],MOD-2))%MOD+1<<'\n';

    return 0;
}