#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n;
double ans,b,c;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        double p;
        cin>>p;
        ans+=(3*b+3*c+1)*p;
        b=(b+c*2+1)*p;
        c=(c+1)*p;
    }
    cout<<ans;
    return 0;
}
