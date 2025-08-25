#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15,MOD=1e18+3;
int f[MN],n;
random_device rd;
mt19937 mt(rd());
vector<bool> notprime(MN+15);
vector<int> prime;
map<int,int> mp;

void init(int n){
    for(int i=2;i<=n;i++){
        if(!notprime[i]){
            prime.push_back(i);
            f[i]=mt()*mt()%MOD*mt()%MOD;
        }
        for(auto p:prime){
            if(p*i>n) break;
            notprime[p*i]=1;
            f[i*p]=f[i]^f[p];
            if(i%p==0){
                break;
            }
        }
    }
}

signed main(){
    init(MN-2);
    cin>>n;
    int x=0;
    for(int i=1;i<=n;i++){
        f[i]^=f[i-1];
        x^=f[i];
    }
    if(!x){
        cout<<n<<'\n';
        for(int i=1;i<=n;i++){
            cout<<i<<' ';
        }
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(x==f[i]){
            cout<<n-1<<'\n';
            for(int j=1;j<=n;j++){
                if(i==j) continue;
                cout<<j<<' ';
            }
            return 0;
        }
    }
    for(int i=1;i<=n;i++) mp[f[i]]=i;
    for(int i=1;i<=n;i++){
        if(mp.count(x^f[i])&&mp[x^f[i]]!=i){
            int p=mp[x^f[i]];
            cout<<n-2<<'\n';
            for(int j=1;j<=n;j++){
                if(i==j||j==p) continue;
                cout<<j<<' ';
            }
            return 0;
        }
    }
            cout<<n-3<<'\n';
            for(int j=1;j<=n;j++){
                if(2==j||j==n||j==n/2) continue;
                cout<<j<<' ';
            }
            return 0;
    

    return 0;
}