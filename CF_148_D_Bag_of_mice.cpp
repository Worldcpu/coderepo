#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int w,b;
double f[MN][MN];


int main(){
    cin>>w>>b;
    for(int i=1;i<=w;i++){
        f[i][0]=1;
    }
    for(int i=1;i<=b;i++){
        f[0][i]=0;
    }
    for(int i=1;i<=w;i++){
        for(int j=1;j<=b;j++){
            f[i][j]+=(double)i/(i+j);
            if(j>=3){
                f[i][j]+=(double)j/(i+j)*(j-1)/(i+j-1)*(j-2)/(i+j-2)*f[i][j-3];
            }
            if(i>=1&&j>=2){
                f[i][j]+=(double)j/(i+j)*(j-1)/(i+j-1)*i/(i+j-2)*f[i-1][j-2];
            }
        }
    }
    cout<<fixed<<setprecision(9)<<f[w][b];
    return 0;
}
