#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
constexpr double eps=1e-8;
int T,n;
double a[MN],b[MN];

bool cmp(double x,double y){
    return fabs(x)<fabs(y);
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=fabs(a[i]);
    }
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+n);
    double r=a[2]/a[1],tmp=r;
    for(int i=2;i<=tmp;i++){
        if(fabs(a[1]*r-a[i])>eps){
            cout<<"No\n";
        }
    }
    bool isneg=0;
    if(a[2]>0) isneg=1;
    for(int i=3;i<=n;i++){
        i
    }
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
