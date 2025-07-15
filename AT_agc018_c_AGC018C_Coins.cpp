#include<bits/stdc++.h>
#define int long long
#define pir pair<bool,int>
using namespace std;
constexpr int MN=1e5+15;
struct Node{
    int f,x,y;
};
int x,y,z,n,a[MN],b[MN],c[MN],ret;

Node check(int x,int y){
    int f=0,xcnt=0,ycnt=0;
    for(int i=1;i<=n;i++){
        if(a[i]+x>b[i]+y){
            if(a[i]+x>0){
                xcnt++;
                f+=a[i]+x;
            }
        }else{
            if(b[i]+y>0){
                ycnt++;
                f+=b[i]+y;
            }
        }
    }
    return {f,xcnt,ycnt};
}

pir checka(int mida){
    int l=-1e9,r=1e9,ans=1e9;
    while(l<=r){
        int midb=(l+r)>>1;
        if(check(mida,midb).y<=y){
            ans=midb;
            l=midb+1;
        }else r=midb-1;
    }
    auto awa=check(mida,ans);
    return pir(awa.x<=x,awa.f-x*mida-y*ans);
}

signed main(){
    cin>>x>>y>>z;
    n=x+y+z;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i]>>c[i];
        a[i]-=c[i],b[i]-=c[i],ret+=c[i];
    }
    int la=-1e9,ra=1e9,ans;
    while(la<=ra){
        int mida=(la+ra)>>1;
        auto qwq=checka(mida);
        if(qwq.first){
            ans=qwq.second;
            la=mida+1;
        }else ra=mida-1;
    }
    cout<<ans+ret;
    return 0;
}
