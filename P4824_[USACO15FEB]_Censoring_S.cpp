#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int MN=1e6+15;
constexpr ull base=13131;
int lena,lenb,tot;
ull a[MN],hshb,pw[MN];
char ans[MN];
string s,t;

int main(){
    cin>>s>>t;
    lena=s.length(),lenb=t.length();
    s=" "+s;
    t=" "+t;
    pw[0]=1;
    for(int i=1;i<=lenb;i++){
        pw[i]=pw[i-1]*base;
        hshb=hshb*base+(t[i]);
    }
    for(int i=1;i<=lena;i++){
        ans[++tot]=s[i];
        a[tot]=a[tot-1]*base+s[i];
        if(hshb==a[tot]-a[tot-lenb]*pw[lenb]){
            tot-=lenb;
        }
    }
    for(int i=1;i<=tot;i++) cout<<ans[i];
    return 0;
}
