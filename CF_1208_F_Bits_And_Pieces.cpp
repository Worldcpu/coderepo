#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=22;
int n,mn[1<<MN],ans;

struct NodeMX{
    int fir,sec;

    friend NodeMX operator +(const NodeMX &x,const NodeMX &y){
        int xmx=x.fir,ymx=y.fir;
        if(xmx<ymx) swap(xmx,ymx);
        return (NodeMX){xmx,max({ymx,x.sec,y.sec})};
    }
}mx[1<<MN];

signed main(){
    memset(mn,0x3f,sizeof(mn));
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        mx[x]=mx[x]+(NodeMX){i,0};
        mn[x]=min(mn[x],i);
    }
    for(int i=0;i<21;i++){
        for(int j=(1<<21)-1;j>=0;j--){
            if(!(j&(1<<i))){
                mx[j]=mx[j]+mx[j^(1<<i)];
                mn[j]=min(mn[j],mn[j^(1<<i)]);
            }
        }
    }
    for(int i=20;i>=0;i--){
        int now=ans|(1<<i);
        bool flag=0;
        for(int j=now;;j=(j-1)&now){
            if(mn[j]<mx[now^j].sec) flag=1;
            if(flag||!j) break;
        }
        if(flag) ans=now;
    }
    cout<<ans;
    return 0;
}
