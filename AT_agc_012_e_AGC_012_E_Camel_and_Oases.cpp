#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,ML=20,INF=0x3f3f3f3f;
int n,V,x[MN],fl[ML][MN],fr[ML][MN];


int main(){
    cin>>n>>V;
    for(int i=1;i<=n;i++){
        cin>>x[i];
    }
    x[0]=-INF-V-1;
    x[n+1]=INF+V+1;
    for(int i=V,cnt=0;i>=0;i>>=1,cnt){
        fr[cnt][n+1]=n+1;
        for(int j=1;j<=n;j++) fl[cnt][i]=(x[i]-x[i-1]<=i)?fl[cnt[i]][]
    }

    return 0;
}