#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
const int MN=15;
const double eps=1e-7;
double a[MN];
int n;
double l,r;
double f(double x){
    double ans=0;
    for(int i=n;i>=0;i--){
        ans=ans*x+a[i];
    }
    return ans;
}
int main(){
    cin>>n>>l>>r;
    for(int i=n;i>=0;i--) cin>>a[i];
    while (r-l>=eps)
    {
        double mid=(l+r)/2;
        if(f(mid+eps)>f(mid-eps)) l=mid;
        else r=mid;
    }
    cout<<fixed<<setprecision(5)<<r;
    return 0;
}