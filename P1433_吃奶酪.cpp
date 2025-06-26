#include<bits/stdc++.h>
using namespace std;
constexpr int MN=17;
int n;
double dis[MN][MN],x[MN],y[MN],f[MN][1<<MN],ret;

double getdis(int a,int b){
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            dis[i][j]=dis[j][i]=getdis(i,j);
        }
    }
    memset(f,127,sizeof(f));
    ret=f[0][0];
    for(int i=1;i<=n;i++){
        f[i][(1<<(i-1))]=getdis(0,i);
    }
    for(int s=1;s<(1<<n);s++){
        for(int i=1;i<=n;i++){
            if(s&(1<<(i-1))){
                for(int j=1;j<=n;j++){
                    if(i==j||!(s&(1<<(j-1)))) continue;
                    f[i][s]=min(f[i][s],f[j][s-(1<<(i-1))]+dis[i][j]);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        ret=min(ret,f[i][(1<<n)-1]);
    }
    cout<<fixed<<setprecision(2)<<ret;
    return 0;
}
