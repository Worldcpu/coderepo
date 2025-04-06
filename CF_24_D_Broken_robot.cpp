#include<bits/stdc++.h>
using namespace std;
const int MN=1200;
const double eps=1e-6;
int n,m,x,y;
double f[MN][MN],mat[MN][MN];

void setmat(int i){
    mat[1][1]=mat[m][m]=2/3.0;
    mat[1][2]=mat[m][m-1]=-1/3.0;
    mat[1][m+1]=f[i+1][1]/3.0+1;
    mat[m][m+1]=f[i+1][m]/3.0+1;
    for(int j=2;j<m;j++){
        mat[j][j]=3/4.0;
        mat[j][m+1]=f[i+1][j]/4.0+1;
        mat[j][j-1]=mat[j][j+1]=-1/4.0;
    }
}

void gauss(){
    for(int i=1;i<=m;i++){
        double d=1.0/mat[i][i];
        mat[i][i]=1.0;//系数化1，主对角线化1
        mat[i][m+1]*=d;//常数变
        if(i!=m){
            mat[i][i+1]*=d;//非对角线化（如果第m列不能这么搞）
            d=mat[i+1][i]/mat[i][i];
            //下一行消3项
            mat[i+1][i]=0;
            mat[i+1][i+1]-=d*mat[i][i+1];
            mat[i+1][m+1]-=d*mat[i][m+1];
        }
    }
    for(int i=m-1;i>=1;i--){
        //回带
        mat[i][m+1]-=mat[i+1][m+1]*mat[i][i+1];
    }
}

int main(){
    cin>>n>>m>>x>>y;
    if(m==1){
        cout<<(2*(n-x));
        return 0;
    }
    for(int i=n-1;i>=x;i--){
        setmat(i);
        gauss();
        for(int j=1;j<=m;j++){
            f[i][j]=mat[j][m+1];
        }
    }
    cout<<fixed<<setprecision(4)<<f[x][y];
    return 0;
}