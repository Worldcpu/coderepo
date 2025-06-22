#include<iostream>
#include<iomanip>
using namespace std;
const int MN=1520;
int n,s;
double f[MN][MN];

int main(){
    cin>>n>>s;
    for(int i=n;i>=0;i--){
        for(int j=s;j>=0;j--){
            if(i==n&&j==s) continue;
            f[i][j]=(f[i][j + 1] * i * (s - j) + f[i + 1][j] * (n - i) * j +f[i + 1][j + 1] * (n - i) * (s - j) + n * s) / (n * s - i * j);
        }
    }
    cout<<fixed<<setprecision(5)<<f[0][0];
    return 0;
}
