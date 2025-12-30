#include<bits/stdc++.h>
using namespace std;
constexpr int MN=15,INF=1e9;
int n,a[MN][4],pos[MN],ans;

namespace SA{
    // bt-> the begin of temperature
    // et-> the end of temperature
    // dt-> delta temperature
    // tim-> the time used for running SA algorithm
    constexpr double Tim=0.98,BT=11451,ET=1e-10,DT=0.9998;

    int getrd(int l,int r){
        return rand()%(r-l+1)+l;
    }
    
    int getf(){
        int ret=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=3;j++){
                ret+=abs(pos[a[i][j]]-pos[i]);
            }
        }
        return ret>>1;
    }

    void SA(){
        ans=INF;
        while(clock()/(1.0*CLOCKS_PER_SEC)<=Tim){
            double temp=BT;
            while(temp>ET){
                int x=getrd(1,n),y=getrd(1,n);
                while(x==y){
                    x=getrd(1,n);
                }
                swap(pos[x],pos[y]);
                auto newf=getf();
                int d=newf-ans;
                if(d<0){
                    ans=newf;
                }else if(double(rand())>exp(double(-d)/temp)*RAND_MAX){
                    swap(pos[x],pos[y]);
                }

                temp=temp*DT;
            }
        }
    }

}

int main(){
    srand(time(0));
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=3;j++) cin>>a[i][j];
        pos[i]=i;
    }
    SA::SA();
    cout<<ans<<'\n';
    

    return 0;
}