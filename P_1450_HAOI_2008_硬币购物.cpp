#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int f[MN],c[5],d[5],n,s;

void init(){
    f[0]=1;
    for(int i=1;i<=4;i++){
        for(int j=c[i];j<=1e5;j++) f[j]+=f[j-c[i]];
    }
}

signed main(){
    cin>>c[1]>>c[2]>>c[3]>>c[4]>>n;
    init();
    while(n--){
        cin>>d[1]>>d[2]>>d[3]>>d[4]>>s;
        int ans=f[s];
        for(int i=1;i<16;i++){
            int num=0,ret=0;
            for(int j=0;j<4;j++){
                if((i>>j)&1){
                    ret+=c[j+1]*(d[j+1]+1);
                }
            }
            if(s>=ret)  ans+=(__builtin_popcountll(i)&1?-1:1)*f[s-ret];
        }
        cout<<ans<<'\n';
    }
    return 0;
}
