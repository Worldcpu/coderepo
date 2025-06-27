#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int MN=1e6+15;
constexpr ull base=23333,MOD=1e9+7;
int n,m,len,ans;
ull pw[MN],hsh[MN];
string s;

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*base%MOD;
}

ull gethsh(int l,int r){
    return (hsh[r]-hsh[l-1]*pw[r-l+1]%MOD+MOD)%MOD;
}

int main(){
    initpw();
    cin>>n>>s;
    s=" "+s;
    for(int i=1;i<=n;i++){
        hsh[i]=(hsh[i-1]*base%MOD+s[i])%MOD;
    }
    m=n/2;
    for(int i=m;i>=0;i--){
        len=min(len+2,m-i);
        while(len>0&&gethsh(i+1,i+len)!=gethsh(n-i+1-len,n-i)) len--;
        if(gethsh(1,i)==gethsh(n-i+1,n)) ans=max(ans,i+len);
    }
    cout<<ans;
    return 0;
}
