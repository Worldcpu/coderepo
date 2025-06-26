#include<bits/stdc++.h>
using namespace std;
const double hjfg=((1.0+sqrt(5.0))/2.0);
double a,b;

int main(){
    cin>>a>>b;
    if(a>b) swap(a,b);
    double ans=(b-a)*hjfg;
    if(ans==a) cout<<0;
    else cout<<1;
    return 0;
}
