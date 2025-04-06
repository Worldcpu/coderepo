#include<iostream>
#define ll long long
using namespace std;
const int MN=3*1e6+15;
ll inv[MN];
void getinv(ll n,ll p){
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(p-p/i)*inv[p%i]%p;
    }
}
int main(){
    ll n,p;
    cin>>n>>p;
    getinv(n,p);
    for(int i=1;i<=n;i++){
        cout<<inv[i]<<"\n";
    }
    return 0;
}