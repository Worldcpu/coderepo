#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MV=1e4+15;
int X[MN],Y[MN],W[MN],n;
double ansx,ansy,answ;
mt19937 mt(0);
uniform_real_distribution<double> gpos(-MV,MV);

namespace SA{
    constexpr double Tim=0.95,BT=1e4,ET=1e-14,DT=0.997;
    uniform_real_distribution<double> genp(0,1);

    double getf(double nowx,double nowy){
        double ret=0;
        for(int i=1;i<=n;i++){
            ret+=hypot(abs(nowx-X[i]),abs(nowy-Y[i]))*W[i];
        }
        return ret;
    }

    void SA(){
        answ=getf(ansx,ansy);

        while(clock()/(1.0*CLOCKS_PER_SEC)<=Tim){
            auto temp=BT;
            while(temp>ET){
                double nowx=ansx+gpos(mt)*temp;    
                double nowy=ansy+gpos(mt)*temp;    

                auto nans=getf(nowx,nowy),d=nans-answ;

                if(d<0){
                    ansx=nowx;
                    ansy=nowy;
                    answ=nans;
                }else if(genp(mt)<=exp(1.0*(-d)/temp)){
                    ansx=nowx;
                    ansy=nowy;
                }

                temp=temp*DT;
            }
        }
    }

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>X[i]>>Y[i]>>W[i];
        ansx+=X[i];
        ansy+=Y[i];
    }   
    ansx/=n;
    ansy/=n;
    SA::SA();
    cout<<fixed<<setprecision(3)<<ansx<<' '<<ansy<<'\n';
    return 0;
}