#include<bits/stdc++.h>
using namespace std;
constexpr int MN=15;
constexpr double eps=1e-6;
int n;
double a[MN][MN],x,mat[MN][MN];

bool gauss(){
    for(int i=1;i<=n;i++){
        //找到第i列第一个非0
        for(int j=i;j<=n;j++){
            if(fabs(mat[j][i])>eps){
                //如果非0
                swap(mat[j],mat[i]);//交换行
                break;
            }
        }
        if(fabs(mat[i][i])<eps){
            return 0;
        }
        for(int j=n+1;j>=i;j--){
            mat[i][j]/=mat[i][i];
        }
        for(int j=i+1;j<=n;j++){
            for(int k=n+1;k>=i;k--){
                mat[j][k]-=mat[j][i]*mat[i][k];
            }
        }
    }
    for(int i=n-1;i>=1;i--){
        for(int j=i+1;j<=n;j++){
            mat[i][n+1]-=mat[i][j]*mat[j][n+1];
        }
    }
    return 1;
}

int main(){
    cin>>n;
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            mat[i][j]=2*(a[i][j]-a[i+1][j]);
            mat[i][n+1]+=a[i][j]*a[i][j]-a[i+1][j]*a[i+1][j];
        }
    }
    gauss();
    for(int i=1;i<=n;i++){
        cout<<fixed<<setprecision(3)<<mat[i][n+1]/mat[i][i]<<' ';
    }
    return 0;
}
