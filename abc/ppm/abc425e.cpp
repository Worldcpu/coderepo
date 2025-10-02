#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5005; 
int T,MOD;
vector<int> prime;
unordered_map<int, vector<int>> pripw,priinv,vpmp;  
unordered_map<int, int> modmp;       
unordered_map<int, int> epmp;        

namespace CRT{
    int mt=1;

    int exgcd(int a,int b,int &x,int &y){
        if(b==0){ x=1; y=0; return a; }
        int x1,y1;
        int d = exgcd(b,a%b,x1,y1);
        x = y1;
        y = x1 - (a/b) * y1;
        return d;
    }
    int inv(int a,int n){
        int x,y;
        int g = exgcd((int)((a%n + n)%n), n, x, y);
        if(g!=1) return -1;
        x %= n; if(x<0) x+=n;
        return x;
    }
    int mul(int x,int y,int mod) 
    {
        __int128 xx = x;
        __int128 yy = y;
        __int128 mm = mod;
        __int128 r = (xx * yy) % mm;
        return (int)r;
    }
}

void pwMOD(int M, vector<pair<int,int>> &fac){
    int x = M;
    for(int i=2;(int)i*i<=x;i++){
        if(x%i==0){
            int cnt=0;
            while(x%i==0){ x/=i; cnt++; }
            fac.emplace_back(i,cnt);
        }
    }
    if(x>1) fac.emplace_back(x,1);
}

void initpw(int MN){
    vector<pair<int,int>> fac;
    pwMOD(MOD, fac);
    CRT::mt = 1;
    for(auto &pe: fac){
        int p = pe.first;
        int e = pe.second;
        int mod = 1;
        for(int i=0;i<e;i++) mod *= p;
        prime.push_back(p);
        modmp[p] = mod;
        epmp[p] = e;
        CRT::mt *= mod; 
        pripw[p].assign(MN+1, 0);
        priinv[p].assign(MN+1, 0);
        vpmp[p].assign(MN+1, 0);
        pripw[p][0]=1;
        vpmp[p][0]=0;
        for(int t=1;t<=MN;t++){
            int x=t; int cnt=0;
            while(x%p==0){ x/=p; cnt++; }
            __int128 cur = (__int128)pripw[p][t-1] * (x % mod);
            pripw[p][t] = (int)(cur % mod);
            vpmp[p][t] = vpmp[p][t-1] + cnt;
        }
        for(int t=0;t<=MN;t++){
            int val = pripw[p][t];
            int g = __gcd(val, mod);
            if(g==1){
                priinv[p][t] = CRT::inv(val, mod);
            }else{
                priinv[p][t] = 0; 
            }
        }
    }
}

int mod_pow(int a,int e,int mod){
    int r=1;
    int A = (a%mod+mod)%mod;
    while(e){
        if(e&1) r = CRT::mul(r, A, mod);
        A = CRT::mul(A, A, mod);
        e >>= 1;
    }
    return (int)r;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T>>MOD;
    initpw(MN);

    while(T--){
        int N; cin>>N;
        vector<int> C(N);
        int S=0;
        for(int i=0;i<N;i++){ cin>>C[i]; S+=C[i]; }
        vector<int> tmp;
        vector<int> mods;
        for(int p: prime){
            int mod = modmp[p];
            int e = epmp[p];
            int v = vpmp[p][S];
            for(int i=0;i<N;i++) v -= vpmp[p][C[i]];
            if(v >= e){
                tmp.push_back(0);
                mods.push_back(mod);
                continue;
            }
            int num = pripw[p][S];
            int den = 1;
            for(int i=0;i<N;i++){
                den = (int)CRT::mul(den, pripw[p][C[i]], mod);
            }
            int den_inv = CRT::inv(den, mod);
            if(den_inv == -1){
                tmp.push_back(0);
                mods.push_back(mod);
                continue;
            }
            int r = (int)CRT::mul(num, den_inv, mod);
            int pv = mod_pow(p, v, mod);
            r = (int)CRT::mul(r, pv, mod);
            tmp.push_back(r);
            mods.push_back(mod);
        }

        int ans = 0;
        int curmod = 1;
        for(int i=0;i<tmp.size();i++){
            int r = tmp[i];
            int m = mods[i];
            if(curmod==1){
                ans = r % m;
                curmod = m;
                continue;
            }
            int cm_mod_m = (int)(curmod % m);
            int invcm = CRT::inv(cm_mod_m, m);
            int diff = (r - (ans % m) + m) % m;
            int t = ( (__int128) diff * invcm ) % m;
            ans = ans + t * curmod;
            curmod = curmod * m;
            ans %= curmod;
            if(ans<0) ans += curmod;
        }
        ans %= MOD;
        if(ans<0) ans+=MOD;
        cout<<ans<<"\n";
    }
    return 0;
}
