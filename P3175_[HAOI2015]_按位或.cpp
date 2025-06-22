#include<bits/stdc++.h>
using namespace std;
constexpr int MN=25;
int n,siz[MN];
double a[MN];


int main(){
    cin>>n;
    n=1<<n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int len=1;len<n;len<<=1){
        for(int p=0;p<n;p+=len*2){
            for(int i=p;i<p+len;i++){
                a[i+len]+=a[i];
            }
        }
    }
    double ans=0;
    for(int i=1;i<n;i++){
        siz[i]=siz[i>>1]+(i&1);
        double tmp=(1-a[i^(n-1)]);
        if(tmp<1e-8){
            cout<<"INF";
            return 0;
        }
        tmp=1/tmp;
        ans+=(siz[i]&1)?-tmp:tmp;
    }
    cout<<fixed<<setprecision(10)<<-ans;
    return 0;
}
