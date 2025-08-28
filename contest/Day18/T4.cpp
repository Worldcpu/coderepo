#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int b[MN],n;
uint64_t x; //uint64_t represents 64-bit unsigned integer

namespace XOR{
    int a[MN];
 uint64_t rand() { //this is a xor-shift random generator
 x ^= x << 13;
 x ^= x >> 7;
 x ^= x << 17;
 return x;
 }
 bool solve() {
 for (int i = 1; i <= n; i++){ //random shuffle [1, 2,..., n]
 a[i] = i;
 swap(a[i], a[rand() % i + 1]);
 }
 for (int i = 1; i <= n; i++){ //print the result
    if(a[i]!=b[i]) return 0;
 }
 return 1;
 }
}

int main(){
    freopen("makedata.in","r",stdin);
    freopen("makedata.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=0;i<=512;i++){
        x=i;
        if(XOR::solve()){
            cout<<i;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
