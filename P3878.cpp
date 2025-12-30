#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=50;
int n,ans,v[MN];
mt19937 mt(random_device{}());

namespace SA{
    constexpr double Tcnt=30,BT=114514,ET=1e-10,DT=0.997;
    uniform_real_distribution<double> genp(0,1);

    int getrd(int l,int r){
        return mt()%(r-l+1)+l;
    }

    int getf(){
        int sum1=0,sum2=0;
        for(int i=1;i<=n/2;i++){
            sum1+=v[i];
        }
        for(int i=n/2+1;i<=n;i++){
            sum2+=v[i];
        }
        return abs(sum1-sum2);
    }

    void SA(){
        int qwq=Tcnt;
        while(qwq--){
            double temp=BT;
            while(temp>ET){
                int x=getrd(1,n/2),y=getrd(n/2+1,n);
                swap(v[x],v[y]);
                int nans=getf(),d=nans-ans;
                if(d<0){
                    ans=nans;
                }else if(genp(mt)>=exp(1.0*(-d)/temp)) swap(v[x],v[y]);
                
                temp*=DT;
            }
        }
    }

}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    ans=SA::getf();
    SA::SA();
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}