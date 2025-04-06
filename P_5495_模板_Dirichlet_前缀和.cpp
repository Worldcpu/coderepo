#include<iostream>
#include<vector>
#define ll long long
const int MN=2e7+15;
using namespace std;
#define uint unsigned int
uint seed;
uint a[MN],b[MN],n;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
vector<int> prime;
vector<bool> notprime(MN);
void eulur(){
    notprime[1]=1;
    for(int i=2;i<MN;i++){
        if(!notprime[i]){
            prime.push_back(i);
        }
        for(ll j=0;prime[j]*i<MN;j++){
            notprime[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
void solve(){
    cin>>n>>seed;
    for(int i=1;i<=n;i++){
        a[i]=getnext();
    }
    for(auto p:prime){
        for(int i=1;p*i<=n;i++){
            a[p*i]+=a[i];
        }
    }
    uint ans=0;
    for(int i=1;i<=n;i++){
        ans^=a[i];
    }
    cout<<ans<<endl;
}
int main(){
    eulur();
    solve();
    return 0;
}