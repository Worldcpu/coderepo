#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
constexpr int MN=1e6+15;
int n;
ll a,b,c,ql,qr;
ll s[MN],f[MN],q[MN];

ld gety(int x){
    return (ld)f[x]+a*s[x]*s[x]-b*s[x];
}

ld getx(int x){
    return (ld)s[x];
}

ld getk(int x,int y){
    return (gety(y)-gety(x))/(getx(y)-getx(x));
}

int main(){
    cin>>n>>a>>b>>c;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        s[i]+=s[i-1];
    }
    ql=1,qr=0;
    q[++qr]=0;
    for(int i=1;i<=n;i++){
        while(ql<qr&&getk(q[ql],q[ql+1])>(2*a*s[i])) ql++;
        f[i]=f[q[ql]]+a*(s[i]-s[q[ql]])*(s[i]-s[q[ql]])+b*(s[i]-s[q[ql]])+c;
        while(ql<qr&&getk(q[qr-1],q[qr])<=getk(q[qr],i)) qr--;
        q[++qr]=i;
    }
    cout<<f[n];
    return 0;
}