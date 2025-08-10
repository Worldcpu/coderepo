#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MS=1<<23;
int n,x,y,U,ans,a[MN],f[2][MS];

int clac(int pos){
    return n/(x+y)+((n%(x+y))>=pos);
}

int main(){
    cin>>n>>x>>y;
    U=(1<<max(x,y))-1;
    memset(f,128,sizeof(f));
    f[0][0]=0;
    int cur;
    for(int i=1,cur=0;i<=x+y;i++){
        cur^=1;
        memset(f[cur],128,sizeof(f[cur]));
        for(int s=0;s<=U;s++){
            int t=(s<<1)&U;
            f[cur][t]=max(f[cur][t],f[cur^1][s]);
            if(!(s&(1<<x-1))&&!(s&(1<<y-1))){
                f[cur][t|1]=max(f[cur][t|1],f[cur^1][s]+clac(i));
            }
        }
    for(int s=0;s<=U;s++){
        ans=max(ans,f[cur][s]);
    }
    }
    cout<<ans;

    return 0;
}
