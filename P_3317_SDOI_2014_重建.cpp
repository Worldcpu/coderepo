#include<bits/stdc++.h>
#define db long double
using namespace std;
constexpr signed MN=55;
constexpr db eps=1e-8;
int n,m;
db a[MN][MN],ret=1;

namespace HLS{

    db solve(){
        db ret=1,w=1;
        for(signed i=1;i<=n;i++){
            for(signed j=i+1;j<=n;j++){
                    db div=a[j][i]/a[i][i];
                    for(signed k=i;k<=n;k++){
                        a[j][k]=(a[j][k]-div*a[i][k]);
                    }  
            }
        }
        for(signed i=1;i<=n;i++){
            ret=a[i][i]*ret;
        }
        return ret;
    }

}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(fabs(a[i][j])<eps){
                a[i][j]=eps;
            }
            if(fabs(1.0-a[i][j])<eps){
                a[i][j]=1.0-eps;
            }
            if(i<j) ret*=1.0-a[i][j];
            a[i][j]=a[i][j]/(1.0-a[i][j]); 
        }
    }
    for(int i=1;i<=n;i++){
        a[i][i]=0;
        for(int j=1;j<=n;j++){
            if(i^j) a[i][i]-=a[i][j];
        }
    }
    n--;
    cout<<fixed<<setprecision(6)<<fabs(HLS::solve()*ret);
}