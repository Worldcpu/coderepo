#include<bits/stdc++.h>
using namespace std;
const int MN=250;
const double eps=1e-6;
double mat[MN][MN];
int n;

int gauss(){
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
            bool flag=1;
            for(int j=i;j<=n;j++){
                if(fabs(mat[i][j])>eps){
                    flag=0;
                    break;
                }
            }
            if(flag&&mat[i][n+1]<eps){
                return -1; 
            }else return 0;
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
        for(int j=1;j<=n+1;j++){
            cin>>mat[i][j];
        }
    }
    int awa=gauss();
    if(awa){
        for(int i=1;i<n+1;i++){
            cout<<"x"<<i<<"="<<fixed<<setprecision(2)<<mat[i][n+1]<<'\n';
        }
    }else cout<<"No Solution";
    return 0;
}