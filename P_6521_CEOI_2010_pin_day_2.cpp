#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int MN=5e4+15,MP=8;
constexpr ull base=13131;
int n,D,ans,pw[MP],f[MN],g[MN];
string st[MN];

void initpw(){
    pw[0]=1;
    for(int i=1;i<MP;i++) pw[i]=pw[i-1]*i;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]/pw[b]/pw[a-b];
}

int main(){
    initpw();
    cin>>n>>D;
    D=4-D;
    for(int i=1;i<=n;i++){
        cin>>st[i];
    }
    for(int s=0;s<16;s++){
        map<ull,int> mp;
        for(int i=1;i<=n;i++){
            ull ret=0;
            for(int j=0;j<4;j++){
                if((s>>j)&1){
                    ret=ret*base+st[i][j];
                }
            }
            g[__builtin_popcount(s)]+=mp[ret];
            ++mp[ret];           
        }
    }
    for(int i=D;i<=4;i++){
        ans+=((i-D)&1?-1:1)*getC(i,D)*g[i];
    }
    cout<<ans;


    return 0;
}