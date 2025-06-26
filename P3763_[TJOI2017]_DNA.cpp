#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr ull base=13131;
constexpr int MN=1e5+15;
int lena,lenb;
ull a[MN],b[MN],pw[MN];
string sa,sb;

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*base;
}

ull hsha(int l,int r){
    return a[r]-a[l-1]*pw[r-l+1];
}

ull hshb(int l,int r){
    return b[r]-b[l-1]*pw[r-l+1];
}

bool binfind(int x){
    int st=1,r=x+lenb-1,ed=lenb;
    for(int i=1;i<=3;i++){
        int lt=-1,rt=ed-st+2,ret=0;
        while(lt+1<rt){
            int mid=(lt+rt)>>1;
            if(hsha(x,x+mid-1)==hshb(st,st+mid-1)) lt=mid;
            else rt=mid;
        }
        x+=lt+1;
        st+=lt+1;
        if(st>ed) return 1;
    }
    return hsha(x,x+lenb-st)==hshb(st,ed);
}

void solve(){
    cin>>sa>>sb;
    lena=sa.length(),lenb=sb.length();
    if(lena<lenb){
        cout<<0<<'\n';
        return;
    }
    sa=" "+sa;
    sb=" "+sb;
    for(int i=1;i<=lena;i++){
        a[i]=a[i-1]*base+sa[i];
    }
    for(int i=1;i<=lenb;i++){
        b[i]=b[i-1]*base+sb[i];
    }
    int ans=0;
    for(int i=1;i<=lena-lenb+1;i++){
        if(binfind(i)) ans++;
    }
    cout<<ans<<'\n';
}

int main(){
    init();
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
