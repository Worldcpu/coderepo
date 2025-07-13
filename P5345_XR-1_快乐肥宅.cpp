#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,a[MN],b[MN],p[MN];
long long c[MN],d[MN];
map<int,int> mp;

int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while (n%i==0) n/=i;
        }
    }
    if(n>=2) ans=ans/n*(n-1);
    return ans;
}

int qpow(int a,int b,int MOD){
    int ret=1;
    while(b){
        if(b&1) ret=1LL*ret*a%MOD;
        a=1LL*a*a%MOD;
        b>>=1;
    }
    return ret;
}

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int BSGS(int a,int b,int p){
    mp.clear();
    b %= p;
    int t = (int)sqrt(p) + 1;
    for (int j = 0; j < t; j++) {
        int val = 1LL * b * qpow(a, j, p) % p;
        mp[val] = j;
    }
    a = qpow(a, t, p);
    if (a == 0) return b == 0 ? 1 : -1e9;
    for (int i = 0; i <= t; i++) {
        int val = qpow(a, i, p);
        if (mp.find(val) == mp.end()) continue;
        int j = mp[val];
        if (1LL * i * t - j >= 0) return i * t - j;
    }
    return -1e9;
}

int exBSGS(int a,int b,int p){
    a %= p; b %= p;
    if(b==1 || p==1) return 0;
    int d, ax = 1, cnt = 0;
    while((d=__gcd(a,p)) != 1){
        if(b % d) return -1e9;
        p /= d;
        b /= d;
        ax = 1LL * ax * (a / d) % p;
        cnt++;
        if(ax == b) return cnt;
    }
    int inv = qpow(ax, phi(p)-1, p);
    b = 1LL * b * inv % p;
    int res = BSGS(a, b, p);
    if(res < 0) return -1e9;
    return res + cnt;
}

int getjie(int m,int a){
    a %= m;
    if(__gcd(a,m)>1) return -1;
    if(a==1) return 1;
    int ret=phi(m),num=ret;
    for(int i=2;i*i<=num;i++){
        if(num%i==0){
            while(num%i==0 && qpow(a,ret/i,m)==1){
                ret/=i;
                num/=i;
            }
            while(num%i==0) num/=i;
        }
    }
    if(num>1 && qpow(a,ret/num,m)==1) ret/=num;
    return ret;
}

int findj(int a,int b,int MOD){
    int gcdd=__gcd(b,MOD);
    MOD/=gcdd;
    if(__gcd(a,MOD)>1) return 1e9+7;
    return getjie(MOD,a);
}

bool merge(long long &a1, long long &p1, long long a2, long long p2) {
    long long k1, k2;
    long long C = ((a2 - a1) % p2 + p2) % p2;
    long long gcdd = __gcd(p1, p2);
    if (C % gcdd) return false;
    exgcd(p1, p2, k1, k2);
    k1 = (k1 % p2 + p2) % p2;
    long long mod = p2 / gcdd;
    a1 = (a1 + (k1 * (C / gcdd) % mod * p1) % (p1 * mod));
    p1 = p1 * mod;
    a1 = (a1 % p1 + p1) % p1;
    return true;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>p[i]>>b[i];
    long long maxx = 0;
    for(int i=1;i<=n;i++){
        c[i]=exBSGS(a[i],b[i],p[i]);
        maxx=max(maxx,c[i]);
        if(c[i] < -1e8){
            cout<<"Impossible\n";
            return 0;
        }
        d[i]=findj(a[i],b[i],p[i]);
        if(d[i] < 0){
            cout<<"Impossible\n";
            return 0;
        }
    }
    long long A=0, M_val=1;
    for(int i=1;i<=n;i++){
        if(M_val<=1e9){
            if(!merge(A,M_val,c[i],d[i])){
                cout<<"Impossible\n";
                return 0;
            }
        }else{
            if(A % d[i] != c[i] % d[i]){
                cout<<"Impossible\n";
                return 0;
            }
        }
    }
    if(A < maxx) A += ((maxx - A + M_val - 1) / M_val) * M_val;
    if(A > 1e9) cout<<"Impossible\n";
    else cout<<A;
    return 0;
}
